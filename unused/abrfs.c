#include <abrfs.h>
#include <ata.h>
#define SIZEOF(object) (char *)(&object+1) - (char *)(&object)

int ceil(float num) {
    int inum = (int)num;
    if (num == (float)inum) {
        return inum;
    }
    return inum + 1;
}

int current_sector = 0x0;
file_t create_file(char name[64], char* data) {
	file_t f;
	f.name = name;
	f.bytes = data;
	f.size = sizeof(data);
	f.sector_number = current_sector;
	f.end_sector = ceil(f.size/512);
	current_sector++;
}
char* convert_f_to_str(file_t file) {
	char* str = "";
	strcat(str, FS_MAGIC); // 8 bytes
	strcat(str, file.name); // 64 bytes
	char* buf;
	strcat(str, itoa(file.size, buf, 10)) // 4 bytes
	char* bufa;
	char* bufb;
	strcat(str, itoa(file.sector_number, bufa, 10));
	strcat(str, itoa(file.end_sector, bufb, 10));
	strcat(str, file.bytes);
	return str;
}
char* convert_str_to_f(char* str) {
	char astr[];
	strcpy(astr, str);
	file_t f;
	char* data;
	for(int i=8; i<72; i++) {
		f.name[i] = str[i];
	}
	for(int i=72; i<76; i++) {
		f.size[i] = str[i];
	}
}