#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdint.h>

typedef struct direntry_s {
  uint8_t status;
  char name[6];
  char ext[3];
  uint8_t attributes;
  uint8_t chars_in_last_block;
  uint16_t blocks_in_file;
  uint8_t first_block_s;
  uint8_t first_block_h;
} direntry;

int main() {
  direntry de;
  char nametemp[11], nametemp2[11];
  unsigned char tmpbuf[131072];
  char *spaces = "            ";
  int ready=0;
  fseek(stdin, 0x4e100, SEEK_SET);
  while (!ready) {
    if (fread(&de, sizeof(de), 1, stdin) != 1) {
      ready = 1;
    } else {
      if (de.name[0] == '\0') {
	ready = 1;
      } else {
	memset(nametemp, 0, sizeof(nametemp));
	strncpy(nametemp, de.name, 6);
	if (de.ext[0] != '\0') {
	  strcat(nametemp, ".");
	  strncat(nametemp, de.ext, 3);
	}
	strcpy(nametemp2, nametemp);
	strncat(nametemp2, spaces, 10-strlen(nametemp));
	printf("%s: Status=0x%02X Attr=0x%02X LBBytes=0x%04X NBlocks=0x%04X (%d bytes) FBlock=(s%02X,h%02X)\n",
	       nametemp2,
	       de.status,
	       de.attributes,
	       de.chars_in_last_block,
	       de.blocks_in_file,
	       de.blocks_in_file * 0x0100,
	       de.first_block_s,
	       de.first_block_h);
	long offs = de.first_block_h * 0x2000 + de.first_block_s * 0x0100;
	long bytes = (de.blocks_in_file - 1) * 0x0100 + de.chars_in_last_block;
	long currpos = ftell(stdin);
	fseek(stdin, offs, SEEK_SET);
	FILE *out = fopen(nametemp, "w");
	int n=fread(tmpbuf, 1, bytes, stdin);
	fwrite(tmpbuf, 1, n, out);
	fclose(out);
	fseek(stdin, currpos, SEEK_SET);
      }
    }
  }
  return 0;
}
