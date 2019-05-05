#!/bin/bash
qpdf --stream-data=uncompress /DATA/Patientendokumente/plz/TMFTools.pdf -| \
iconv -f ISO-8859-1 -t UTF-8//TRANSLIT | \
sed -n ':a;/^[^-].*Td$/d;/^-.*Td$/bb;/^\[/!bb;/TJ$/!bb; s/\([^\\]\))[^(]*(/\1/g; s/^\[[^(]*(//;s/)[^])]*]TJ$//;s/\\(/(/g;s/\\)/)/g;H;n;ba;  :b;s/.*//;x;/./{s/\n//g;p};' >ausg3
