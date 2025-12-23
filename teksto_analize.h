#ifndef TEKSTO_ANALIZE_H_INCLUDED
#define TEKSTO_ANALIZE_H_INCLUDED

#include <string>
#include <map>
#include <set>
#include <ostream>

using std::string;
using std::map;
using std::set;
using std::pair;
using std::ostream;

string pakeisti_zodi(const string& zodis);

void spausdinti_suskaiciuotus_zodzius(const map<string, int>& zodziu_skaicius);

void spausdinti_zodziu_eilutes(const map<string, pair<int, set<int>>>& zodziu_eilute);

string pasirinkti_url();

void spausdinti_url(ostream& out, const set<string>& url_set);

void paskirstyti_url(const string& pasirinkimas, const set<string>& url_set);

void darbas_su_failu();

#endif