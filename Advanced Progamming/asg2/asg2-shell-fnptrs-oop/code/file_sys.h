// $Id: file_sys.h,v 1.7 2019-07-09 14:05:44-07 - - $

#ifndef __INODE_H__
#define __INODE_H__

#include <exception>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>
using namespace std;

#include "util.h"

// inode_t -
//    An inode is either a directory or a plain file.

enum class file_type {PLAIN_TYPE, DIRECTORY_TYPE};
class inode;         // Inception Dream Machine
class base_file;
class plain_file;
class directory;
using inode_ptr = shared_ptr<inode>;
using base_file_ptr = shared_ptr<base_file>;
ostream& operator<< (ostream&, file_type);


// inode_state -
//    A small convenient class to maintain the state of the simulated
//    process:  the root (/), the current directory (.), and the
//    prompt.

class inode_state {
   friend class inode;
   friend ostream& operator<< (ostream& out, const inode_state&);
   private:
      inode_ptr root {nullptr}; // Start of the Dream
      inode_ptr cwd {nullptr};  // Totem to check what dream were in 
      string prompt_ {"% "};
   public:
      inode_state (const inode_state&) = delete; // copy ctor
      inode_state& operator= (const inode_state&) = delete; // op=
      inode_state();
      ~inode_state();
      inode_ptr get_cwd() {return cwd;}
      inode_ptr get_root() {return root;}
      void set_cwd(inode_ptr current){cwd = current;}
      string get_prompt(){return prompt_;}
      void set_prompt(string new_prompt) {prompt_= new_prompt;}
      const string& prompt() const;
};

// class inode -
// inode ctor -
//    Create a new inode of the given type.
// get_inode_nr -
//    Retrieves the serial number of the inode.  Inode numbers are
//    allocated in sequence by small integer.
// size -
//    Returns the size of an inode.  For a directory, this is the
//    number of dirents.  For a text file, the number of characters
//    when printed (the sum of the lengths of each word, plus the
//    number of words.
//    

class inode {
   friend class inode_state;
   private:
      static size_t next_inode_nr;
      size_t inode_nr;
      base_file_ptr contents;
   public:
      inode (file_type);
      int get_inode_nr() const;
      base_file_ptr get_contents(){return contents;}
};


// class base_file -
// Just a base class at which an inode can point.  No data or
// functions.  Makes the synthesized members useable only from
// the derived classes.

class file_error: public runtime_error {
   public:
      explicit file_error (const string& what);
};

class base_file {
   protected:
      base_file() = default;
      virtual const string& error_file_type() const = 0;
   public:
      virtual ~base_file() = default;
      base_file (const base_file&) = delete;
      base_file& operator= (const base_file&) = delete;
      virtual size_t size() const = 0;
      virtual const wordvec& readfile() const;
      virtual void writefile (const wordvec& newdata);
      virtual map<string,inode_ptr>& getDirents(){throw file_error("is a "+ error_file_type());}
      virtual void remove (const string& filename);
      virtual inode_ptr mkdir (const string& dirname);
      virtual inode_ptr mkfile (const string& filename);

      // Helpers
      virtual string get_pathName(){throw file_error("is a "+ error_file_type());}
      virtual void set_pathName (const string& ){throw file_error("is a "+ error_file_type());}
      virtual void get_listing(){throw file_error("is a "+ error_file_type());}
      virtual int get_type(){throw file_error("is a "+ error_file_type());}
      virtual void set_type(int){throw file_error("is a "+ error_file_type());}
      virtual inode_ptr valid_pathName(inode_ptr , const wordvec& , int ){throw file_error("is a "+ error_file_type());}
      virtual bool name_unique(string){throw file_error("is a "+ error_file_type());}
      virtual void print_data(){throw file_error("is a "+ error_file_type());}
      virtual void ls_recur(inode_ptr ){throw file_error("is a "+ error_file_type());}
      virtual void dir_rm(){throw file_error("is a "+ error_file_type());}
      virtual void dir_rmr(){throw file_error("is a "+ error_file_type());}
      virtual string get_name(){throw file_error("is a "+ error_file_type());}
      virtual void set_name(string s){throw file_error("is a "+ error_file_type());}
      virtual void destroy(const string s){throw file_error("is a "+ error_file_type());}
};

// class plain_file -
// Used to hold data.
// synthesized default ctor -
//    Default vector<string> is a an empty vector.
// readfile -
//    Returns a copy of the contents of the wordvec in the file.
// writefile -
//    Replaces the contents of a file with new contents.

class plain_file: public base_file {
   private:
      int type;   // 0: DIR || 1: FILE
      wordvec data;
	  size_t fileSize;
      virtual const string& error_file_type() const override {
         static const string result = "plain file";
         return result;
      }
   public:
      virtual size_t size() const override;
      virtual const wordvec& readfile() const override;
      virtual void writefile (const wordvec& newdata) override;
      virtual int get_type() override {return type;}
      virtual void set_type(int typed) override {type = typed;} 
      virtual void print_data() override;
      virtual void destroy(const string s) override;

      // Helper
};

// class directory -
// Used to map filenames onto inode pointers.
// default ctor -
//    Creates a new map with keys "." and "..".
// remove -
//    Removes the file or subdirectory from the current inode.
//    Throws an file_error if this is not a directory, the file
//    does not exist, or the subdirectory is not empty.
//    Here empty means the only entries are dot (.) and dotdot (..).
// mkdir -  
//    Creates a new directory under the current directory and 
//    immediately adds the directories dot (.) and dotdot (..) to it.
//    Note that the parent (..) of / is / itself.  It is an error
//    if the entry already exists.
// mkfile -
//    Create a new empty text file with the given name.  Error if
//    a dirent with that name exists.

class directory: public base_file {
   private:
      // Must be a map, not unordered_map, so printing is lexicographic
      map<string,inode_ptr> dirents;
      virtual const string& error_file_type() const override {
         static const string result = "directory";
         return result;
      }
      string pathName;
      int type;         // 0: DIR || 1: FILE
      string name;
   public:
      virtual size_t size() const override;
      virtual void remove (const string& filename) override;
      virtual inode_ptr mkdir (const string& dirname) override;
      virtual map<string,inode_ptr>& getDirents()override {return dirents;}
      virtual inode_ptr mkfile (const string& filename) override;

      // Helpers
      virtual string get_pathName() override {return pathName;}
      virtual void set_pathName (const string& dirname) override {pathName = dirname;}
      virtual int get_type() override {return type;}
      virtual void set_type(int typed) override {type = typed;} 
      virtual void get_listing() override;
      virtual inode_ptr valid_pathName(inode_ptr pt, const wordvec& parse, int depth) override;
      virtual bool name_unique(string unique) override;
      virtual void ls_recur(inode_ptr dir) override;
      virtual void dir_rm() override;
      virtual void dir_rmr() override;
      virtual string get_name() override {return name;}
      virtual void set_name(string s) override {name = s;}
};

#endif


// cd a/aa/b > root.
// /a/aa/aaa/aaaa