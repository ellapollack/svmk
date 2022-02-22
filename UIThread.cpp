#include <map>
#include "UIThread.h"
#include <sys/ioctl.h>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <termios.h>

#define say(str) write(1,str,sizeof(str))
// #define move(x,y) say("\x1b[" y ";" x "H")
// #include "ncurses.h"

void sayWithBackground(char* string, bool blackNotWhite)
{

}

UIThread::UIThread(const char* threadName, soul::patch::SOULPatchAudioProcessor* patch)
      : Thread(threadName),
        patch(patch)
{
    startThread(5);
}

UIThread::~UIThread()
{
    stopThread(-1);
}

struct termios initial;

void cleanup(void) {
    //clean up the alternate buffer
    say("\x1b[2J");

    //switch back to the normal buffer
    say("\x1b[?1049l");

    //show the cursor again
    // say("\x1b[?25h");

	tcsetattr(1, TCSANOW, &initial);
}

void cleanup_die(int i) {
    std::exit(1);
}

void resize(int i) {
    // spurious argument needed so that the
    // function signature matches what signal(3) expects

    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);

    // from here, call a function to repaint the screen
    // (probably starting with "\x1b[2J")

    int halfWidth = ws.ws_col / 2;
    int halfHeight = ws.ws_row / 2;
    int left = halfWidth - 5;
    int top = halfHeight - 2;

	//clean up the buffer
	say("\x1b[2J");
    say("\x1b[0;0H"); // move to 0,0

    while (left-- > 0)
    {
        say("\x1b[1C");
    }
    while (top-- > 0)
    {
        say("\x1b[1B");
    }

    // paint keyboard

    say("\u001b[37m"); // white text
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("2");
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("3");
    say("\u001b[47m"); // white background
    say("  ");
    say("\u001b[40m"); // black background
    say("5");
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("6");
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("7");
    say("\u001b[47m"); // white background
    say("  ");
    say("\u001b[40m"); // black background
    say("9");
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("0");
    say("\u001b[47m"); // white background
    say("  ");
    say("\u001b[40m"); // black background
    say("=");
    say("\u001b[47m"); // white background
    say(" ");
    for (int col = 20; col > 0; col--)
    {
        say("\x1b[1D"); // left
    }
    say("\x1b[1B"); // down
    
    say("\u001b[30m"); // black text
    say("\u001b[47m"); // white background
    say("q");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("w");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("er");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("t");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("y");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("ui");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("o");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("p[");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("]");
    for (int col = 30; col > 0; col--)
    {
        say("\x1b[1D"); // left
    }
    say("\x1b[2B"); // down
    say("\u001b[37m"); // white text
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("s");
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("d");
    say("\u001b[47m"); // white background
    say("  ");
    say("\u001b[40m"); // black background
    say("g");
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("h");
    say("\u001b[47m"); // white background
    say("  ");
    say("\u001b[40m"); // black background
    say("k");
    say("\u001b[47m"); // white background
    say(" ");
    say("\u001b[40m"); // black background
    say("l");
    say("\u001b[47m"); // white background
    say("  ");
    say("\u001b[40m"); // black background
    say("'");
    for (int col = 17; col > 0; col--)
    {
        say("\x1b[1D"); // left
    }
    say("\x1b[1B"); // down
    say("\u001b[30m"); // black text
    say("\u001b[47m"); // white background
    say("z");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("x");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("cv");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("b");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("nm");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say(",");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[47m"); // white background
    say("./");
    say("\u001b[40m"); // black background
    say(" ");
    say("\u001b[0m"); // reset colors
    say("\x1b[0;0H"); // move to 0,0
}

void terminit(void) {
	struct termios t;
	tcgetattr(1, &t);
	initial = t;
	t.c_lflag &= (~ECHO & ~ICANON);
	tcsetattr(1, TCSANOW, &t);

    //enter the alternate buffer
	say("\x1b[?1049h");

	std::signal(SIGWINCH, resize);
	resize(0);

	//hide the cursor
	say("\x1b[?25l");

	//register our cleanup function
	std::atexit(cleanup);
	std::signal(SIGTERM, cleanup_die);
	std::signal(SIGINT,  cleanup_die);
}

void UIThread::run() {

    terminit();

    const int EGOCOLS = 16;
    const int EGOLINES = 16;

    // say("Press any key to play a sound, then press ESC to quit.");

    std::map<char, uint8_t> keymap;
    const char keys[97] = R"(ZXCVBNM<>?  ASDFGHJKL:" QWERTYUIOP{}!@#$%^&*()_+zxcvbnm,./  asdfghjkl;' qwertyuiop[]1234567890-=)";
    for (uint8_t i=0; i<strlen(keys); ++i) if (keys[i] != ' ') keymap[keys[i]] = i;

    char next='\0', prev;
    while (next != '\x1b') {
        prev = next;
        read(1, &next, 1);
        if (keymap.count(prev) > 0)
        {
        auto noteOff = juce::MidiMessage::noteOff(1, keymap[prev], 0.f).getRawData();
            patch->injectMIDIMessage(noteOff[0], noteOff[1], noteOff[2]);
        }
        if (keymap.count(next) > 0)
        {
            auto noteOn = juce::MidiMessage::noteOn(1, keymap[next], 1.0f).getRawData();
            patch->injectMIDIMessage(noteOn[0], noteOn[1], noteOn[2]);
        }
    }

    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}