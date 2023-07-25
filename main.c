#include <common/log.h>
#include <openra1n.h>
#include <stdbool.h>

int main(int argc, char **argv) {
	LOG_RAINBOW("-=-=- openra1n -=-=-");
	LOG_INFO("Waiting for DFU mode device");
    bool ret;
	ret = openra1n() ? 0 : 1;
	return ret;
}