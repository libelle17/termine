#!/bin/bash
blau="\033[1;34m";
gruen="\033[1;32m";
dblau="\033[0;34;1;47m";
rot="\033[1;31m";
lila="\033[1;35m";
reset="\033[0m";
QVZ=/DATA/Patientendokumente/plz;
QDT=$QVZ/TMFTools.pdf;
tbtab=tmptermine;
urtab=termine;
obschreib=;
dbhil=$(dirname $0)/termhil.sql;
dbupd=$(dirname $0)/termupd.sql;
printf "dbhil: $blau$dbhil$reset\n";
if test $tbtab = $urtab; then printf "'${blau}$urtab$reset' nicht als Name von ${blau}tbtab$reset erlaubt! Breche ab.\n"; exit; fi;
lm=$(stat -c "%Y" "$QDT" 2>/dev/null) # last modification im Format epoch
if test "$lm"; then
  if test $(echo $lm|grep "^[0-9]*$"); then  
    printf "$blau%s$reset = Änderungsdatum von $blau$QDT$reset\n" "$(stat -c "%y" "$QDT")";
    sql="SELECT UNIX_TIMESTAMP(MAX(abgerufen)) FROM "$urtab
    le=$(mariadb --defaults-extra-file=~/.mariadbpwd quelle -s -e"$sql" 2>/dev/null) # letzte Einlesung
    if test $(echo $le|grep "^[0-9]*$"); then  
      printf "$blau%s$reset                 = letzte Terminspeicherung mit Einlesung laut ${blau}quelle->$urtab$reset\n" "$(date --date @$le +"%Y-%m-%d %H:%M:%S")"
      if test "$lm" -gt "$le"; then
        obschreib=ja;
      else
        printf "$blau$QDT$reset (geändert: $blau%s$reset) schon verarbeitet\n" "$(stat -c '%y' "$QDT")";
      fi;
    else
      printf "Fehler bei der Datenbankabfrage: $blau$sql$reset\n";
      obschreib=ja;
    fi;
  else
    printf "letztes Änderungsdatum von $blau$QDT$reset nicht ermittelbar.\n";
    obschreib=ja;
  fi;
else
  printf "$QDT fehlt!\n";
fi;
if test "$obschreib"; then
printf "rufe auf: ${blau}pdftotext $QDT$reset\n"
# pdftotext $QDT -layout
NEUQDT=$(echo $QDT|sed 's/\(.*\).pdf$/\1.txt/');
printf "dies hat erstellt: $blau$NEUQDT$reset\n";
# echo "START TRANSACTION;" > "$dbhil";
printf "" > "$dbhil";
echo "START TRANSACTION;" > "$dbupd";
echo "SET @vorher=(SELECT COUNT(0) FROM $urtab);" >> "$dbupd";
# echo "DROP TABLE IF EXISTS $tbtab;" >> "$dbhil";
sql=$(cat <<EOF
CREATE TABLE $tbtab (
	id INT(10) NOT NULL AUTO_INCREMENT COMMENT 'eindeutige ID, Prim',
	taid INT(10) NULL DEFAULT NULL COMMENT 'Bezug auf terminakt',
	pid INT(10) NULL DEFAULT NULL COMMENT 'Pat_Id aus namen',
	zp DATETIME NULL DEFAULT NULL COMMENT 'Terminzeitpunkt',
	raum VARCHAR(100) NULL DEFAULT NULL COMMENT 'Terminart' COLLATE 'utf8mb4_german2_ci',
	zusatz VARCHAR(400) NULL DEFAULT NULL COMMENT 'Terminbeschreibung und eintragender Mitarbeiter' COLLATE 'utf8mb4_german2_ci',
	aktzeit DATETIME NULL DEFAULT NULL COMMENT 'Zeitpunkt der Aktualisierung',
	abgerufen DATETIME NULL DEFAULT NULL COMMENT 'UTC-Dateiänderung',
	gebdat DATETIME NULL DEFAULT NULL COMMENT 'in Klammern angegebenes Geburtsdatum',
	FVorlauf TINYINT(6) NOT NULL DEFAULT '0' COMMENT 'FVorlauf aus MO, -32767 => 0',
	PRIMARY KEY (id) USING BTREE,
	INDEX zp (zp) USING BTREE,
	INDEX pid (pid) USING BTREE,
	INDEX taid (taid) USING BTREE,
	INDEX raum (raum(30)) USING BTREE
)
COLLATE='utf8mb4_german2_ci'
ENGINE=InnoDB
ROW_FORMAT=DYNAMIC;
EOF
)
# echo "$sql" >> "$dbhil";
# echo mariadb --defaults-extra-file=~/.mariadbpwd quelle < "$dbhil";
# mariadb --defaults-extra-file=~/.mariadbpwd quelle < "$dbhil";
abgerufen=$(stat -c "%y" "$QDT");
abgerufen=${abgerufen:0:19};
aktzeit=$(date +"%Y-%m-%d %H:%M:%S")
printf "INSERT INTO $urtab(pid,zp,zusatz,raum,aktzeit,abgerufen,gebdat) VALUES " >> $dbhil
awk -v azt="$aktzeit" -v abg="$abgerufen" '
 function isnum(x,f) {switch (typeof(x)) {case "strnum": case "number": return 1; case "string": return (split(x, f, " ") == 1) && (typeof(f[1]) == "strnum"); default: return 0 } }
  function ltrim(s) { sub(/^[ \t\r\n]+/, "", s); return s }
  function rtrim(s) { sub(/[ \t\r\n]+$/, "", s); return s }
  function trim(s)  { return rtrim(ltrim(s)); }
{
  if (match($0,"  Nr.") && !gesetzt){
    gesetzt=1;
    b[1]=1;
    e[1]=match($0,"Nr.")+3-b[1];
    b[2]=e[1]+2;
    e[2]=match($0,"PNr.")+4-b[2];
    b[3]=e[2]+2;
    b[4]=match($0,"Datum");
    e[3]=b[4]-2-b[3]-b[3];
    b[5]=match($0,"Uhr");
    e[4]=b[5]-2-b[4];
    b[6]=match($0,"Patient");
    e[5]=b[6]-2-b[5];
    b[7]=match($0,"Terminart");
    e[6]=b[7]-2-b[6];
    b[8]=match($0,"Zusatz");
    e[7]=b[8]-2-b[7];
  }
  if (match($0,"==")==1) {
    an=!an;
  } else if (an) {
    if ($0 ~ "^ *$") {
    } else {
/*    print $0; */
    tdat=trim(substr($0,b[4],e[4])); datum=substr(tdat,7,4)"-"substr(tdat,4,2)"-"substr(tdat,1,2);
    pat=trim(substr($0,b[6],e[6])); gsub(/'\''/,"'\'\''",pat);
    gb=gensub(/.*([0-9]{2}\.[0-9]{2}\.[0-9]{4}).*/,"\\1",1,pat);
    if (gb ~ "^[0-9.]{10}$") gb=substr(gb,7,4)"-"substr(gb,4,2)"-"substr(gb,1,2); else gb="1899-12-30";
    zusatz=trim(substr($0,b[8])); gsub(/'\''/,"'\'\''",zusatz);
    pid=ltrim(substr($0,b[2],e[2])); if (pid=="") pid="0"; else {
       printf "DELETE FROM termine WHERE zp>='\''"datum"'\'' AND pid="pid" AND aktzeit<'\''"azt"'\'';\n" >> "'$dbupd'";
    }
    sql="('\''"pid"'\'','\''"datum" "trim(substr($0,b[5],e[5]))"'\'','\''"zusatz"'\'','\''"trim(substr($0,b[7],e[7]))"'\'','\''"azt"'\'','\''"abg"'\'','\''"gb"'\'')";
    znr=znr+1;
    if (znr>1) printf "," >> "'$dbhil'";
    printf sql >> "'$dbhil'";
    }
  }
}' $NEUQDT;
# printf ";\nCOMMIT;\n" >> "$dbhil";
echo ";\nSET @nachins=(SELECT COUNT(0) FROM $urtab);" >> "$dbhil";
echo "SET @nachloe=(SELECT COUNT(0) FROM $urtab);" >> "$dbupd";
cat "$dbhil" >> "$dbupd";
printf ";\nUPDATE $urtab t JOIN $urtab v ON t.pid=v.pid AND t.zp=v.zp AND t.raum=v.raum AND TRIM(REPLACE(t.zusatz,'\n',''))='' AND TRIM(REPLACE(v.zusatz,'\n','') NOT IN ('','..','...','n')) SET t.zusatz=v.zusatz;\n" >> "$dbupd";
echo "SET @nachupd=(SELECT COUNT(0) FROM $urtab);" >> "$dbupd";
printf "DELETE FROM $urtab WHERE EXISTS(SELECT 0 FROM $urtab v WHERE pid=$urtab.pid AND zp=$urtab.zp AND raum=$urtab.raum and zusatz=$urtab.zusatz AND aktzeit<$urtab.aktzeit);" >> "$dbupd";
echo "SET @doppupd=(SELECT COUNT(0) FROM $urtab);" >> "$dbupd";
echo "SELECT CONCAT('vorher:    ',@vorher) zahlen UNION SELECT CONCAT('nachloe:   ',@nachloe) UNION SELECT CONCAT('nachins:   ',@nachins) UNION SELECT CONCAT('nachupd:   ',@nachupd) UNION SELECT CONCAT('dopploe:   ',@dopploe);" >> "$dbloe";
echo "COMMIT;" >> "$dbupd";
# mariadb --defaults-extra-file=~/.mariadbpwd quelle < "$dbhil";
mariadb --defaults-extra-file=~/.mariadbpwd quelle < "$dbupd";
fi;
  # print isnum($0), $0 >> "'$dbhil'"
