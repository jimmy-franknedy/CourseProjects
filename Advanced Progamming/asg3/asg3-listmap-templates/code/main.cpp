// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <regex>
#include <cassert>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

void do_ops(str_str_map& m);
void do_ops_file(str_str_map& m,vector<string>s);

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         default:
            complain() << "-" << char (optopt) << ": invalid option"
                       << endl;
            break;
      }
   }
}

int main (int argc, char** argv) {
   sys_info::execname (argv[0]);
   scan_options (argc, argv);
   str_str_map test;
   vector <string> v;
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
      str_str_pair pair (*argp, to_string<int> (argp - argv));
      cout << "Before insert: " << pair << endl;
      v.push_back(*argp);
   }
   if(v.size() > 0) do_ops_file(test,v);
   else do_ops(test);
   cout << test.empty() << endl;
   for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }
   str_str_map::iterator itor = test.begin();
   test.erase (itor);
   cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

void do_ops(str_str_map& m)
{
   regex comment_regex {R"(^\s*(#.*)?$)"};
   regex key_value_regex {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
   regex trimmed_regex {R"(^\s*([^=]+?)\s*$)"};
   smatch sm;
   int count = 1;
   while(1)
   {
      string line;
      getline (cin, line);
      if (cin.eof()) break;
      cout << "-" << ": " << count << ": " << line << endl;
      ++count;
      smatch result;
      if (regex_search (line, result, comment_regex)) 
      {
         // cout << "Comment or empty line." << endl;
         continue;
      }
      if (regex_search (line, result, key_value_regex)) 
      {
         // cout << "key  : \"" << result[1] << "\"" << endl;
         // cout << "value: \"" << result[2] << "\"" << endl;
         if(result[1].length() > 0 and result[2].length() > 0)
         {
            cout << result[1] << " = " << result[2] << endl;
            str_str_pair pair(result[1], result[2]);
            m.insert(pair);
         }
         else if (result[1].length() > 0 and result[2].length() == 0)
         {
            if(m.find(result[1])!= m.end()) m.erase(m.find(result[1]));
         }
         else if (result[1].length() == 0 and result[2].length() > 0)
         {
            for(auto ltp = m.begin(); ltp != m.end(); ++ltp)
            {
               if(ltp->second.compare(result[2]) == 0)
               {
                  cout << ltp->first << " = " << ltp->second << endl;
               }
            }
         }
         else
         {
            for(auto ltp = m.begin(); ltp != m.end(); ++ltp)
            {
               cout << ltp->first << " = " << ltp->second << endl;
            }
         }
      }
      else if (regex_search (line, result, trimmed_regex)) 
      {
         // cout << "query: \"" << result[1] << "\"" << endl;
         if(m.find(result[1]) == m.end())
         {
            cerr << result[1] << ": key not found" << endl;
            sys_info::exit_status(1);
         }
         else
         {
            cout << result[1] << " = " 
            << m.find(result[1])->second << endl;
         }
      }
      else 
      {
         assert (false and "This can not happen.");
      }
   }
   while(m.begin()!= m.end()) m.erase(m.begin());
}

// file
void do_ops_file(str_str_map& m,vector<string>s)
{
   regex comment_regex {R"(^\s*(#.*)?$)"};
   regex key_value_regex {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
   regex trimmed_regex {R"(^\s*([^=]+?)\s*$)"};
   smatch sm;
   size_t index;
   for(index = 0 ; index < s.size(); ++index)
   {
      ifstream infile;
      infile.open(s.at(index));
      if(s.at(index).compare("-") == 0)
      {
         do_ops(m);
         continue;
      }
      else if(infile.fail())
      {
         cerr << "Invalid file read" << endl;
         sys_info::exit_status(1);
      }
      else
      {
         int count = 1;
         while(1)
         {
            string line;
            getline (infile, line);
            if (infile.eof()) break;
            cout << s.at(index) << ": " << count << ": "<< line<<endl;
            ++count;
            smatch result;
            if (regex_search (line, result, comment_regex)) 
            {
               // cout << "Comment or empty line." << endl;
               continue;
            }
            if (regex_search (line, result, key_value_regex)) 
            {
               // cout << "key  : \"" << result[1] << "\"" << endl;
               // cout << "value: \"" << result[2] << "\"" << endl;
               if(result[1].length() > 0 and result[2].length() > 0)
               {
                  // cout << "k=v case" << endl;
                  cout << result[1] << " = " << result[2] << endl;
                  str_str_pair pair(result[1], result[2]);
                  m.insert(pair);
               }
               else if (result[1].length() > 0 and 
                  result[2].length() == 0)
               {
                  // cout << "k= case" << endl;
                  if(m.find(result[1]) != m.end())
                  {
                     m.erase(m.find(result[1]));
                  }
               }
               else if (result[1].length() == 0 and 
                  result[2].length() > 0)
               {
                  // cout << "=v case" << endl;
                  for(auto ltp = m.begin(); ltp != m.end(); ++ltp)
                  {
                     if(ltp->second.compare(result[2]) == 0)
                     {
                        cout << ltp->first << " = " 
                        << ltp->second << endl;
                     }
                  }
               }
               else
               {
                  for(auto ltp = m.begin(); ltp != m.end(); ++ltp)
                  {
                     cout << ltp->first << " = " << ltp->second<<endl;
                  }
               }
            }
            else if (regex_search (line, result, trimmed_regex)) 
            {
               // cout << "query: \"" << result[1] << "\"" << endl;
               if(m.find(result[1]) == m.end())
               {
                  cerr << result[1] << ": key not found" << endl;
                  sys_info::exit_status(1);
               }
               else
               {
                  cout << result[1] << " = " 
                  << m.find(result[1])->second << endl;
               }
            }
            else 
            {
               assert (false and "This can not happen.");
            }
         }
      }
   }
   while(m.begin()!= m.end()) m.erase(m.begin());
}
