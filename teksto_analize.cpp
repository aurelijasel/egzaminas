#include "bibliotekos.h"
#include "teksto_analize.h"
#include <sstream>
#include <locale>
#include <codecvt>
#include <string>
#include <cwctype>

string pakeisti_zodi(const string& zodis) {
    std::locale loc("lt_LT.UTF-8");
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring w_zodis = converter.from_bytes(zodis);
    std::wstring w_naujas;

    for (wchar_t wc : w_zodis) {
        if (!iswpunct(wc) && !iswdigit(wc)) {
            wc = std::use_facet<std::ctype<wchar_t>>(loc).tolower(wc);
            w_naujas += wc;
        }
    }

    return converter.to_bytes(w_naujas);
}

void spausdinti_suskaiciuotus_zodzius(const map<string, int>& zodziu_skaicius) {
    ofstream failas("zodziu_skaicius.txt");
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo 'kiekis.txt'!" << endl;
        return;
    }

    failas << left << setw(20) << "Zodis" << setw(10) << "Skaicius" << endl;
    failas << string(30, '-') << endl;

    for (map<string, int>::const_iterator it = zodziu_skaicius.begin(); it != zodziu_skaicius.end(); ++it) {
        if (it->second > 1) {
            failas << left << setw(20) << it->first << setw(10) << it->second << endl;
        }
    }

    cout << "Rezultatai issaugoti faile 'zodziu_skaicius.txt'" << endl;
}

void spausdinti_zodziu_eilutes(const map<string, pair<int, set<int>>>& zodziu_eilute) {
    ofstream failas("zodziu_eilute.txt");
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo 'zodziu_eilute.txt'" << endl;
        return;
    }

    failas << left << setw(20) << "Zodis" << "Eilutes" << endl;
    failas << string(40, '-') << endl;

    for (map<string, pair<int, set<int>>>::const_iterator it = zodziu_eilute.begin(); it != zodziu_eilute.end(); ++it) {
        const string& zodis = it->first;
        const pair<int, set<int>>& duomenys = it->second;

        if (duomenys.first > 1) {
            failas << left << setw(20) << zodis << "{";
            bool pirmas = true;
            for (set<int>::const_iterator sit = duomenys.second.begin(); sit != duomenys.second.end(); ++sit) {
                if (!pirmas) failas << ", ";
                failas << *sit;
                pirmas = false;
            }
            failas << "}" << endl;
        }
    }

    cout << "Rezultatai issaugoti faile 'zodziu_eilute.txt'" << endl;
}

string pasirinkti_url() {
    string pasirinkimas;
    cout << "Pasirinkite kur rodyti URL (terminalas - T, failas - F): ";
    while (true) {
        cin >> pasirinkimas;
        transform(pasirinkimas.begin(), pasirinkimas.end(), pasirinkimas.begin(), ::toupper);
        if (pasirinkimas == "T" || pasirinkimas == "F") break;
        cout << "Netinkama ivestis. Bandykite dar karta: ";
    }
    return pasirinkimas;
}

void spausdinti_url(std::ostream& out, const set<string>& url_set) {
    out << "Rasti URL:" << endl;
    for (set<string>::const_iterator it = url_set.begin(); it != url_set.end(); ++it) {
        out << *it << endl;
    }
}

void paskirstyti_url(const string& pasirinkimas, const set<string>& url_set) {
    if (pasirinkimas == "T") {
        spausdinti_url(cout, url_set);
    }
    else {
        ofstream failas("url_sarasas.txt");
        if (failas.is_open()) {
            spausdinti_url(failas, url_set);
            cout << "Rezultatai issaugoti faile 'url_sarasas.txt'" << endl;
        }
        else {
            cout << "Nepavyko sukurti 'url_sarasas.txt'" << endl;
        }
    }
}

void darbas_su_failu() {
    string failo_pavadinimas;
    ifstream failas;

    map<string, int> zodziu_skaicius;
    map<string, pair<int, set<int>>> zodziu_eilute;
    set<string> url_set;
    int eil_nr = 0;

    std::regex url_regex(R"((https?:\/\/)?(www\.)?[a-zA-Z0-9-]+\.[a-zA-Z]{2,}(/[^\s]*)?)");

    cout << "Iveskite failo pavadinima: ";
    getline(cin, failo_pavadinimas);

    while (!failas.is_open()) {
        failas.open(failo_pavadinimas);
        if (!failas.is_open()) {
            cout << "Failas nerastas. Bandykite dar karta: ";
            getline(cin, failo_pavadinimas);
        }
    }

    string eilute;
    while (getline(failas, eilute)) {
        eil_nr++;
        std::stringstream ss(eilute);
        string zodis;
        while (ss >> zodis) {
            if (std::regex_search(zodis, url_regex)) {

                if (zodis.size() >= 4 &&
                    isupper((unsigned char)zodis[0]) &&
                    zodis[1] == '.' &&
                    isupper((unsigned char)zodis[2])) {
                    continue;
                }

                if (zodis.find("//") != string::npos &&
                    zodis.find("http") != 0) {
                    continue;
                }

                if (zodis.find("http") != 0 && zodis.find("www.") != 0) {
                    size_t dot = zodis.find('.');
                    if (dot != string::npos && dot <= 1) {
                        continue;
                    }
                }

                if (zodis.find(".//") != string::npos) {
                    continue;
                }

                while (!zodis.empty() && ispunct((unsigned char)zodis.back())) {
                    zodis.pop_back();
                }

                url_set.insert(zodis);
            }
            else {
                string tvarkytas = pakeisti_zodi(zodis);
                if (!tvarkytas.empty()) {

                    bool turi_raidziu = false;
                    for (char c : tvarkytas) {
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                            turi_raidziu = true;
                            break;
                        }
                    }
                    if (!turi_raidziu) continue;

                    zodziu_skaicius[tvarkytas]++;
                    zodziu_eilute[tvarkytas].first++;
                    zodziu_eilute[tvarkytas].second.insert(eil_nr);
                }
            }
        }
    }

    failas.close();

    spausdinti_suskaiciuotus_zodzius(zodziu_skaicius);
    spausdinti_zodziu_eilutes(zodziu_eilute);

    if (!url_set.empty()) {
        string pasirinkimas = pasirinkti_url();
        paskirstyti_url(pasirinkimas, url_set);
    }
    else {
        cout << "URL adresu nerasta." << endl;
    }
}