// $Id: file_sys.cpp,v 1.7 2019-07-09 14:05:44-07 - - $

#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <iomanip>

using namespace std;

#include "debug.h"
#include "file_sys.h"

size_t inode::next_inode_nr {1};

struct file_type_hash {
   size_t operator() (file_type type) const {
      return static_cast<size_t> (type);
   }
};

ostream& operator<< (ostream& out, file_type type) {
   static unordered_map<file_type,string,file_type_hash> hash {
      {file_type::PLAIN_TYPE, "PLAIN_TYPE"},
      {file_type::DIRECTORY_TYPE, "DIRECTORY_TYPE"},
   };
   return out << hash[type];
}

// *DONE*
inode_state::inode_state() {
   DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt() << "\"");
   root = make_shared<inode>(file_type::DIRECTORY_TYPE);
   cwd = root;
   root->get_contents()->getDirents().insert(pair<string,inode_ptr>(".",root));
   root->get_contents()->getDirents().insert(pair<string,inode_ptr>("..",root));
}

// (~D) *DONE* 
inode_state::~inode_state(){
	cwd = root;
   root->get_contents()->dir_rmr();
   root->get_contents()->getDirents().clear();
}


const string& inode_state::prompt() const { return prompt_; }

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

inode::inode(file_type type): inode_nr (next_inode_nr++) {
   switch (type) {
      case file_type::PLAIN_TYPE:
           contents = make_shared<plain_file>();
           break;
      case file_type::DIRECTORY_TYPE:
           contents = make_shared<directory>();
           break;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

// *DONE*
int inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}


file_error::file_error (const string& what):
            runtime_error (what) {
}

// *DONE*
const wordvec& base_file::readfile() const {
   throw file_error ("is a " + error_file_type());
}

// *DONE*
void base_file::writefile (const wordvec&) {
   throw file_error ("is a " + error_file_type());
}

// *DONE*
void base_file::remove (const string&) {
   throw file_error ("is a " + error_file_type());
}

// *DONE*
inode_ptr base_file::mkdir (const string&) {
   throw file_error ("is a " + error_file_type());

}

// *DONE*
inode_ptr base_file::mkfile (const string&) {
   throw file_error ("is a " + error_file_type());
}


size_t plain_file::size() const {
   // DEBUGF ('i', "size = " << size);
   return fileSize;
}

// *DONE*
const wordvec& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}

// *DONE*
void plain_file::writefile (const wordvec& words) {
   DEBUGF ('i', words);
   
   size_t charCount = 0;
   data.clear();
   data.resize(words.size()-2);
   int bound = words.size();
   for(auto index = 2; index < bound; index++)
   {
	  if(index > 2)
		  charCount += 1;
      data.at(index-2) = words.at(index);
	  charCount += data.at(index-2).length();
   }
   fileSize = charCount;
}

// *DONE*
size_t directory::size() const {
   // DEBUGF ('i', "size = " << size);
   return dirents.size();
}

void directory::remove (const string& filename) {
   DEBUGF ('i', filename);
}

// *DONE*
inode_ptr directory::mkdir (const string& dirname) {
   DEBUGF ('i', dirname);
   inode_ptr dirchild = make_shared<inode>(file_type::DIRECTORY_TYPE);
   dirchild->get_contents()->set_type(0);
   dirchild->get_contents()->set_pathName(this->get_pathName()+ "/" + dirname);
   dirchild->get_contents()->getDirents().insert(pair<string,inode_ptr>(".",dirchild));
   dirchild->get_contents()->getDirents().insert(pair<string,inode_ptr>("..",this->getDirents().at(".")));
   dirchild->get_contents()->set_name(dirname);
   return dirchild;
}

// *DONE*
inode_ptr directory::mkfile (const string& filename) {
   DEBUGF ('i', filename);
   inode_ptr filechild = make_shared<inode>(file_type::PLAIN_TYPE);
   filechild->get_contents()->set_type(1);
   return filechild;
}

// *DONE*
void directory::get_listing()
{
   for(auto index = dirents.begin(); index != dirents.end(); index++)
   {
   	// if(index->second == nullptr) continue;
      cout << setw(6) << index->second->get_inode_nr();
      cout << " " << setw(6) << index->second->get_contents()->size() << " ";
      cout << index->first;
	  if(index->second->get_contents()->get_type() == 1)
		  cout << endl;
      else if(index->second->get_contents()->get_type() == 0) cout << "/" << endl;
   }
}

// *DONE*
inode_ptr directory::valid_pathName(inode_ptr pt, const wordvec& parse, int depth)
{
   int check_size = parse.size()-1;
   auto check = pt->get_contents()->getDirents().find(parse[depth]);

   // if the key is VALID, AND we are done parsing
   if(depth == check_size && check != pt->get_contents()->getDirents().end() && check->second->get_contents()->get_type()==0)
   {
      // return that pointer
      return check->second;
   }
   // if the key is VALID, BUT we are not done parsing
   else if(depth != check_size && check != pt->get_contents()->getDirents().end() && check->second->get_contents()->get_type()==0)
   {
      // recur
      return valid_pathName(check->second,parse,depth+1);
   }
   // if the key is NOT VALID
   else
   {
      return nullptr;
   }
}

// *DONE*
bool directory::name_unique(string unique)
{
   // if the given name is unique, return true!
   return (dirents.find(unique) == dirents.end() ? true : false);
}

// *DONE*
void plain_file::print_data()
{
   for(size_t index = 0; index <= data.size()-1; index++)
   {
      cout << data.at(index);
      if(index != data.size()-1) cout << " ";
   }
   cout << endl;
}
void directory::dir_rm()
{

}

// *DONE*
void directory::ls_recur(inode_ptr dir)
{
   // print out the cwd
   cout << dir->get_contents()->get_pathName() + ":" <<  endl;

   // print out the contents of the directory
   dir->get_contents()->get_listing();

   // start recursion
   auto index = dir->get_contents()->getDirents().begin();
   while(index != dir->get_contents()->getDirents().end())
   {
      // cout << index->first << ": of type[" << index->second->get_contents()->get_type() << "]" << endl;
      // if the basefile is a directory
      if(index->second->get_contents()->get_type() == 0)
      {
         // make sure that we are not looking at "." or ".."
         if(index->first.compare(".") != 0 and index->first.compare("..") != 0)
         {
            ls_recur(index->second);
         }
      }
      // increment iterator position
      index++;
   }
}

// (~D) *DONE*
void plain_file::destroy(const string s)
{
   // intentionally left blank for convenience
   data.clear();
}

// (~D) *DONE*
void directory::dir_rmr()
{
	for(auto index = dirents.begin(); index != dirents.end();)
	{
		int update = 0;
		if(index->first.compare(".") != 0 and index->first.compare("..") != 0)
		{
			if(index->second->get_contents()->get_type() == 0)
			{
				// don't need to do anything if its a file
				index->second->get_contents()->dir_rmr();
				index->second->get_contents()->getDirents().clear();
			}
			if(dirents.find(index->first) != dirents.end())
			{
				index = dirents.erase(index);
				update = 1;
			}
		}
		if(not update) ++index;
	}
}
