#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME_SIZE 256
#define BUF_SIZE 512

int load_file(const char* filename){
  return open(filename, O_RDONLY);
}

bool isCapital(const char c){
  if(c > 64 && c < 91) return true;

  return false;
}

bool isLetter(const char c){
  if((c > 64 && c < 91) || (c > 96 && c < 123)) return true;

  return false;
}

void wooblify(int fp, const char* filename){
  char buf[BUF_SIZE], woobly_filename[FILENAME_SIZE];

  sprintf(woobly_filename, "%s%s", filename,"_woobly");

  int woobly_fp = open(woobly_filename, O_CREAT | O_WRONLY, 0755);

  bool curCapital = true;
  int bytes;
  while((bytes = read(fp, buf, BUF_SIZE)) > 0){
    // wooblify the buffer
    for(int i = 0 ; i < bytes ; i++){
 
      if(!isLetter(buf[i]))
        continue;

      if(isCapital(buf[i]) && !curCapital) buf[i] += 32;

      else if(!isCapital(buf[i]) && curCapital) buf[i] -= 32;

      curCapital = !curCapital;
    }

    // write buf to file

    write(woobly_fp, buf, bytes);
  }
}

int main(int argc, char** argv){
  if(argc < 2){
    printf("[ERR] - Not enough arguments - woobly <file> ...\n");
    return -1;
  }

  for(int i = 1 ; i < argc ; i++){
    int fp = load_file(argv[i]);

    if(strlen(argv[i]) == 0){
      printf("[WAR] - Couldn't wooblify file %s - it doesn't exist...\n", argv[i]);
      continue;
    }

    wooblify(fp, argv[i]);
    printf("%s has been wooblified!\n", argv[i]); 
  }


  return 0;
}
