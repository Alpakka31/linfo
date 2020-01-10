#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>
#include <pwd.h>
#include "config.h"

/*
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

#
#  Copyright (c) 2020 by Alpakka31
#
*/

const std::string APP_NAME = "Linfo";
const std::string APP_VERSION = "v0.1";

std::string getUser() {
    uid_t uid = getuid();
    struct passwd* pw = getpwuid(uid);
    if (pw) {
        return std::string(pw->pw_name);
    } else if (!pw) {
        fprintf(stderr, "Virhe: Käyttäjänimen saaminen epäonnistui!\n");
        exit(EXIT_FAILURE);
    }
}

std::string getShell() {
    uid_t uid = getuid();
    struct passwd* pw = getpwuid(uid);
    if (pw) {
        return std::string(pw->pw_shell);
    } else if (!pw) {
        fprintf(stderr, "Virhe: Komentotulkin saaminen epäonnistui\n");
        exit(EXIT_FAILURE);
    }
}

uid_t getUserID() {
    uid_t uid = getuid();
    return uid;
}

std::string getHostname() {
    char konenimi[20];
    int tulos = gethostname(konenimi, 20);
    if (tulos != 0) {
        fprintf(stderr, "Virhe: Konenimen saaminen epäonnistui!\n");
        exit(EXIT_FAILURE);
    }

    return std::string(konenimi);
}

std::string getKernel() {
    struct utsname kernel;
    uname(&kernel);
    char* release = kernel.release;
    char* sysname = kernel.sysname;
    std::string combine = std::string(sysname) + " " + std::string(release);
    return combine;
}

void getPkgs() {

    FILE *fp;
    char data[64];
    std::string pkgamount = "pkginfo -i | wc -l";
    fp = popen(pkgamount.c_str(), "r");
    if (fp == NULL) {
        fprintf(stderr, "Virhe: Asennettujen pakettien määrää ei voitu saada!\n");
        exit(EXIT_FAILURE);
    } else {
        while (fgets(data, 64, fp) != NULL) {
            fprintf(stdout, "Paketit: %s", data);
        }
    }
}

void showInfo() {
    std::cout << "Jakelu: " << OS_NAME << "\n";
    std::cout << "Jakelumuoto: " << OS_RMODEL << "\n";
    std::cout << "Ydin: " << getKernel() << "\n";
    std::cout << "Käyttäjä: " << getUser() << "\n";
    std::cout << "UID: " << getUserID() << "\n";
    std::cout << "Komentotulkki: " << getShell() << "\n";
    std::cout << "Konenimi: " << getHostname() << "\n";

    // pkgutils toimii ainoastaan tällä hetkellä
    if (SHOW_PKGS == "k") {
        getPkgs();
    }
}

void showUsage() {
    std::cout << "Käyttö: linfo [valinta]\n\n";
    std::cout << "  -u | --usage    [tämä ruutu]\n";
    std::cout << "  -v | --version  [näytä version]\n";
    std::cout << "  -s | --show     [näytä järjestelmästä infoa]\n\n";
}

int main(int argc, char** argv) {

    if (OS_NAME == "") {
        fprintf(stderr, "Virhe: Sinun pitää määrittää jakelun nimi!\n");
        exit(EXIT_FAILURE);
    }
    if (OS_RMODEL == "") {
        fprintf(stderr, "Virhe: Sinun pitää määrittää jakelunmuoto!\n");
        exit(EXIT_FAILURE);
    }

    // Jos argumentteja ei ole annettu, niin näytä miten ohjelmaa käytetään
    if (argc <= 1) {
        showUsage();
    }

    // Ratko annetut argumentit
    for (int i = 0; i < argc; i++) {
        std::string opt = argv[i];

        if (opt == "-v" || opt == "--version") {
            std::cout << APP_NAME << " " << APP_VERSION << "\n";
        } else if (opt == "-u" || opt == "--usage") {
            showUsage();
        } else if (opt == "-s" || opt == "--show") {
            showInfo();
        }
    }
    return EXIT_SUCCESS;
}