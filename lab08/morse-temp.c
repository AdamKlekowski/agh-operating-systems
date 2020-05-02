/* Przy użyciu odpowiednich funkcji i flag, ustanów nowe atrybuty terminala
(zmodyfikuj odpowiednie wartości w polach struktury termios),
aby w trakcie działania programu odczytywane były rzeczywiście pojedyncze znaki,
a program dla każdej wczytywanej litery wyświetlał od razu jej odpowiednik
w alfabecie Morse'a (przy czym program ma nie wyświetlać samej litery!). */

#include <string.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void) {
  char *kod[]={".- ","-... ","-.-. ","-.. ",". ","..-. ","--. ",".... ",".. ",".--- ",
	        "-.- ",".-.. ","-- ","-. ","--- ",".--. ","--.- ",".-. ","... ","- ",
	        "..- ","...- ",".-- ","-..- ","-.-- ","--.. "};
  char bufor[6] = "";
  char znak;

  enableRawMode();

  while(read(0,&znak,1) && znak != '\n') {
      strcpy(bufor, kod[znak - 'a']);
      write(1, bufor, 6);
  }

  disableRawMode();
  
  return 0;
}
