
ASN1_DEFS = etsi_cam.asn1 etsi_894_2.asn1

ASN1_OBJS=${ASN_MODULE_SOURCES:.c=.o}

all:
	make Makefile.am.sample
	make cam_size

cam_size: cam_size.o Makefile.am.Sample
	clang -o cam_size cam_size.o $(ASN1_OBJS)

include Makefile.am.sample

cam_size.o: cam_size.c
	clang -I. -c cam_size.c

Makefile.am.sample: $(ASN1_DEFS)
	asn1c -gen-PER -pdu=CAM etsi_cam.asn1 etsi_894_2.asn1

