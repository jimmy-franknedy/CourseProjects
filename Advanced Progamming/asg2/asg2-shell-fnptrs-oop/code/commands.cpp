// $Id: commands.cpp,v 1.18 2019-10-08 13:55:31-07 - - $

#include "commands.h"
#include "debug.h"

command_hash cmd_hash {
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
   {"rmr"   , fn_rmr   },
   {"#"     , fn_comm  },
};

// *DONE*
command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   DEBUGF ('c', "[" << cmd << "]");
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
		throw command_error (cmd + ": no such function");
   }
   return result->second;
}

command_error::command_error (const string& what):
	runtime_error (what) {
}

int exit_status_message() {
	int status = exec::status();
	cout << exec::execname() << ": exit(" << status << ")" << endl;
	return status;
}

// *DONE*
void fn_comm (inode_state& , const wordvec&)
{

}

// *DONE*
void fn_cat (inode_state& state, const wordvec& words){
	DEBUGF ('c', state);
	DEBUGF ('c', words);
   // CASE: "cat (space)" or "cat"
   if(words.size() == 1)
   {
   	// return error and exit :: no filename/path specified
      throw command_error (words[0] + ": No argument specified.");
      exec::status(1);
   }
   // ASSUME: possibility of multiple arguments
   for(size_t i = 0; i < words.size()-1; i++)
   {
   	// CASE: "cat /" "cat (.)" "cat (..)"
	   if(words[i+1].compare("/") == 0 || words[i+1].compare(".") == 0 || words[i+1].compare("..") == 0)
	   {
	      // return error and exit :: filename/path is to a directory
	      throw command_error (words[0] + ": Filename is to a directory that already exists!");
	      exec::status(1);
	   }
	   else
	   {
	   	string rooted = words[i+1];
	      int start_root = 0;
	      if(rooted[0] == '/') start_root = 1;
	      wordvec isolate = split(words[i+1],"/");
	      inode_ptr temp;
	      string save = isolate.at(isolate.size()-1);
	      // CASE: given a filepath/filename
	      if(isolate.size() == 1)
	      {
	      	// CASE: given "cat /test" or given "cat test"
	         if(start_root) temp = state.get_root();
	         else temp = state.get_cwd();
	      }
	      // CASE: given a pathname
	      else
	      {
	         isolate.pop_back();
	         // CASE: path starts from the root
	         if(start_root) temp = state.get_cwd()->get_contents()->valid_pathName(state.get_root(),isolate,0);

	         // CASE: path starts from the cwd
	         else temp = state.get_cwd()->get_contents()->valid_pathName(state.get_cwd(),isolate,0);
	      }
	      if(temp == nullptr)
	      {
	         // return error and exit :: filepath does not exist
	         throw command_error (words[0] + ": Given filepath does not exist.");
	         exec::status(1);
	      }
	      if(temp->get_contents()->getDirents().find(save) == temp->get_contents()->getDirents().end())
	      {
	      	 // return error and exit :: filepath does not exist
	         throw command_error (words[0] + ": Give filename does not exist in filepath.");
	         exec::status(1);
	      }
	      if(temp->get_contents()->getDirents().at(save)->get_contents()->get_type() == 0)
	      {
	         // return error and exit :: filename/path is to a directory
	         throw command_error (words[0] + ": Given path exists but is to a directory.");
	         exec::status(1);
	      }
	      temp->get_contents()->getDirents().at(save)->get_contents()->print_data();
	   }
   }
}

// *DONE*
void fn_cd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // CASE: "cd (space)" or "cd"
   if(words.size() == 1) state.set_cwd(state.get_root());
   else if (words.size() > 2)
   {
		// return error and exit :: too many commands to "cd"
      throw command_error (words[0] + ": Too many arguments for command.");
      exec::status(1);
   }
   // CASE: "cd (arg)"
   else
   {
      // CASE: "cd /"
      if(words[1].compare("/") == 0) state.set_cwd(state.get_root());

      // CASE: "cd (pathname)"
      else
      {
         string rooted = words[1];
         int start_root = 0;
         if(rooted[0] == '/') start_root = 1;
         wordvec isolate = split(words[1],"/");
         inode_ptr temp;
         // CASE: "cd (pathname)" starts from root
         if(start_root) temp = state.get_cwd()->get_contents()->valid_pathName(state.get_root(),isolate,0);
         // CASE: "cd (pathname)" starts from cwd
         else temp = state.get_cwd()->get_contents()->valid_pathName(state.get_cwd(),isolate,0);
         if(temp == nullptr)
         {
            // return error and exit: pathname DNE
            throw command_error (words[0] + ": Given directory path does not exist.");
            exec::status(1);
         }
         state.set_cwd(temp);
      }
   }
}

// *DONE*
void fn_echo (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}

// *DONE*
void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   string temp = "";
   if(words.size() > 1)
   {
      for(size_t index = 1; index < words.size(); ++index)
      {
         temp += words[index];
      }
      for(size_t index = 0; index < temp.size(); ++index)
      {
         if(isalpha(temp[index]))
         {
            exec::status(127);         
            throw ysh_exit();
         }
      }
      int err = stoi(temp);
      exec::status(err);
   }
   throw ysh_exit();
}

// *DONE*
void fn_ls (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // CASE: "ls" "ls (space)"
   if(words.size() == 1)
   {
      if(state.get_cwd() == state.get_root()) cout << "/:" << endl;
      else cout << state.get_cwd()->get_contents()->get_pathName() + ":" << endl;
      state.get_cwd()->get_contents()->get_listing();
   }
   // CASE: "ls (arg1) (arg2) (arg3)"
   else
   {
   	for(size_t i = 0; i < words.size()-1; ++i)
   	{
   		// CASE: "ls (.)" "ls (..)"
		   if(words[i+1].compare(".") == 0 || words[i+1].compare("..") == 0)
		   {
		      cout << words[i+1] + ":" << endl;
		      state.get_cwd()->get_contents()->getDirents().at(words[1])->get_contents()->get_listing();
		   }
		   // CASE: "ls (/)"
		   else if(words[i+1].compare("/") == 0)
		   {
		      cout << "/:" << endl;
		      state.get_root()->get_contents()->get_listing();
		   }

		   // CASE: "ls (pathname)"
		   else
		   {
		      int start_root = 0;
		      string rooted = words[i+1];
		      if(rooted[0] == '/') start_root = 1;
		      inode_ptr temp;
		      wordvec isolate = split(words[i+1],"/");
		      // CASE: path starts from the root 
		      if(start_root) temp = state.get_cwd()->get_contents()->valid_pathName(state.get_root(),isolate,0);
		      // CASE: path starts from the cd
		      else temp = state.get_cwd()->get_contents()->valid_pathName(state.get_cwd(),isolate,0);
		      // if the directory does not exists
		      if(temp == nullptr)
		      {
		         // return error and exit
		         throw command_error (words[0] + ": Given directory path does not exist.");
		         exec::status(1);
		      }
		      cout << words[i+1] + ":" << endl;
		      temp->get_contents()->get_listing();
		   }
   	}
   }
}

// *DONE*
void fn_lsr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // ASSUME: possibility of multiple arguments
   // CASE: "lsr" "lsr (space)"
   if(words.size() == 1)
   {
      cout << "/";
      state.get_cwd()->get_contents()->ls_recur(state.get_cwd());
   }
   else
   {
      // CASE: multiple arguments
      for(size_t i = 0; i < words.size()-1; i++)
      {
         // CASE: "lsr (.)" "lsr (..)"
         if(words[i+1].compare(".") == 0 or words[i+1].compare("..") == 0)
         {
            // CASE: "lsr (.)" "lsr (..)" is root!
            if(state.get_root() == state.get_cwd()->get_contents()->getDirents().at(words[i+1]))
            {
               cout << "/";
            }
            state.get_cwd()->get_contents()->ls_recur(state.get_cwd()->get_contents()->getDirents().at(words[i+1]));
         }

         // CASE: "lsr (/)"
         else if(words[i+1].compare("/") == 0)
         {
            cout << "/";
            state.get_cwd()->get_contents()->ls_recur(state.get_root());
         }

         // CASE: given directory path
         else
         {
            int start_root = 0;
            string rooted = words[i+1];
            if(rooted[0] == '/') start_root = 1;
            inode_ptr temp;
            wordvec isolate = split(words[i+1],"/");
            // CASE: path starts from the root 
            if(start_root)
            {
               temp = state.get_cwd()->get_contents()->valid_pathName(state.get_root(),isolate,0);
            }
            // CASE: path starts from the cd
            else
            {
               temp = state.get_cwd()->get_contents()->valid_pathName(state.get_cwd(),isolate,0);
            }
            // if path exists
            if(temp == nullptr)
            {
               // return error and exit
               throw command_error (words[0] + ": Given directory path does not exist.");
               exec::status(1);
            }
            if(start_root) cout << "/" << endl;
            state.get_cwd()->get_contents()->ls_recur(temp);
         }
      }
   }
}

// *DONE*
void fn_make (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // ASSUME: words[1] could be a file name or directory path!
   // CASE: "make" "make (space)"
   if(words.size() == 1)
   {
      // return error and exit
      throw command_error (words[0] + ": No argument specified.");
      exec::status(1);
   }

   // CASE: "make (.)" "make (..)" "make (/)"
   if(words[1].compare(".") == 0 || words[1].compare("..") == 0 || words[1].compare("/") == 0)
   {
      // return error and exit
      throw command_error (words[0] + ": Argument already exists and is of directory type.");
      exec::status(1);
   }

   int start_root = 0;
   string rooted = words[1];
   if(rooted[0] == '/') start_root = 1;
   inode_ptr temp;
   wordvec isolate = split(words[1],"/");
   string save = isolate.at(isolate.size()-1);
   // CASE: "make test" "make /test"
   if(isolate.size() == 1)
   {
      if(start_root) temp = state.get_root();
      else temp = state.get_cwd();
   }
   // CASE: "make /a/apple" "a/apple"
   else
   {
      isolate.pop_back();
      if(start_root) temp = state.get_cwd()->get_contents()->valid_pathName(state.get_root(),isolate,0);
      else temp = state.get_cwd()->get_contents()->valid_pathName(state.get_cwd(),isolate,0);
   }
   // CHECK: if the directory exists
   if(temp == nullptr)
   {
      // return error and exit
      throw command_error (words[0] + ": Directory path oes not exist.");
      exec::status(1);
   }
   // CHECK: if the name exists
   if(temp->get_contents()->name_unique(save))
   {
      temp->get_contents()->getDirents().insert(pair<string,inode_ptr>(save,temp->get_contents()->mkfile(save)));
   }
   // CHECK: if the name is a FILETYPE
   if(temp->get_contents()->getDirents().at(save)->get_contents()->get_type()==0)
   {
      // return error and exit
      throw command_error (words[0] + ": Path is to a type directory.");
      exec::status(1);
   }
   temp->get_contents()->getDirents().at(save)->get_contents()->writefile(words);
}

// *DONE*
void fn_mkdir (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // ASSUME: words[1] could be a file name or directory path!
   // CASE: "mkdir" "mkdir (space)"
   if(words.size() == 1)
   {
      // return error and exit
      throw command_error (words[0] + ": No argument specified.");
      exec::status(1);
   }
   else
   {
   	for(size_t i = 0; i < words.size()-1; i++)
   	{
   		// CASE: "make (.)" "make (..)" "make (/)"
		   if(words[i+1].compare(".") == 0 || words[i+1].compare("..") == 0 || words[i+1].compare("/") == 0)
		   {
		      // return error and exit
		      throw command_error (words[0] + ": Invalid Argument.");
		      exec::status(1);
		   }
		   int start_root = 0;
		   string rooted = words[i+1];
		   if(rooted[0] == '/') start_root = 1;
		   inode_ptr temp;
		   wordvec isolate = split(words[i+1],"/");
		   string save = isolate.at(isolate.size()-1);
		   // CASE: "mkdir (test)" "mkdir (/test)"
		   if(isolate.size() == 1)
		   {
		      if(start_root) temp = state.get_root();
		      else temp = state.get_cwd();
		   }
		   // CASE: "mkdir (/a/aa/aaa)" "mkdir (a/aa/aaa)"
		   else
		   {
		      isolate.pop_back();
		      if(start_root) temp = state.get_cwd()->get_contents()->valid_pathName(state.get_root(),isolate,0);
		      else temp = state.get_cwd()->get_contents()->valid_pathName(state.get_cwd(),isolate,0);
		   }
		   // CHECK: if parent directory exists
		   if(temp == nullptr)
		   {
		      // return error and exit
		      throw command_error (words[0] + ": Directory path does not exist.");
		      exec::status(1);
		   }
		   // CHECK: if directory to be made does not already exist
		   if(temp->get_contents()->name_unique(save) == false)
		   {
		      // return error and exit:: a directory with 'that' name already exists
		      throw command_error (words[0] + ": Directory already exists.");
		      exec::status(1);
		   }
		   temp->get_contents()->getDirents().insert(pair<string,inode_ptr>(save,temp->get_contents()->mkdir(save)));
   	}
   }
}

// *DONE*
void fn_prompt (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   state.set_prompt(words[1]+" ");
}

// *DONE*
void fn_pwd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(state.get_cwd() == state.get_root()) cout << "/" << endl;
   else cout << state.get_cwd()->get_contents()->get_pathName() << endl;
}

// *DONE* (NOT THROUGHLY TESTED IN GIVEN TEST FILES)
void fn_rm (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // CASE: "rm" "rm (space)"
   if(words.size() == 1)
   {
      // return error and exit
      throw command_error (words[0] + ": No argument specified.");
      exec::status(1);
   }
   else if(words.size() > 2)
   {
   	throw command_error (words[0] + ": Too many arguments for command.");
      exec::status(1);
   }
   // CASE: "rm (.)" "rm (..)" "rm (/)"
   else if (words[1].compare(".") == 0 || words[1].compare("..") == 0 || words[1].compare("/") == 0)
   {
   	throw command_error (words[0] + ": Invalid Argument! Not an empty directory.");
      exec::status(1);
   }
   else
   {
      int start_root = 0;
      string rooted = words[1];
      if(rooted[0] == '/') start_root = 1;
      inode_ptr temp;
      wordvec isolate = split(words[1],"/");
      string save = isolate.at(isolate.size()-1);
      if(isolate.size() == 1)
      {
         if(start_root) temp = state.get_root();
         else temp = state.get_cwd();
      }
      else
      {
         isolate.pop_back();
         if(start_root) temp = state.get_cwd()->get_contents()->valid_pathName(state.get_root(),isolate,0);
         else temp = state.get_cwd()->get_contents()->valid_pathName(state.get_cwd(),isolate,0);
      }
      // CHECK: if parent path EXISTS
      if(temp == nullptr)
      {
         // return error and exit
         throw command_error (words[0] + ": Directory path does not exist.");
         exec::status(1);
      }
      // CHECK: if file/directory to be deleted does NOT EXIST
      if(temp->get_contents()->name_unique(save))
      {
         // return error and exit:: target does not exist in parent DIR.
         throw command_error (words[0] + ": Target to be removed does not exist!");
         exec::status(1);
      }
      // CASE: removing a file **DOUBLE CHECK THIS**
      if(temp->get_contents()->getDirents().at(save)->get_contents()->get_type())
      {
         temp->get_contents()->getDirents().at(save)->get_contents()->destroy(save);
         temp->get_contents()->getDirents().erase(save);
      }
      // CASE: removing a dir
      else
      {
         if(temp->get_contents()->getDirents().at(save)->get_contents()->getDirents().size() > 2)
         {
            // return error and exit:: target DIR is NOT EMPTY
            throw command_error (words[0] + ": Target to be removed is a directory that is not empty!");
            exec::status(1);      
         }
         temp->get_contents()->getDirents().at(save)->get_contents()->getDirents().clear();
         temp->get_contents()->getDirents().erase(save);         
      }
   }
}

// *DONE*
void fn_rmr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   // CASE: "rmr" "rmr (space)"
   if(words.size() == 1)
   {
      // return error and exit
      throw command_error (words[0] + ": No argument specified.");
      exec::status(1);
   }
   else if(words.size() > 2)
   {
   	throw command_error (words[0] + ": Too many arguments for command.");
      exec::status(1);
   }
   // CASE: "rmr (.)" "rmr (..)" "rmr (/)"
   else if (words[1].compare(".") == 0)
   {
   	// state.get_cwd()->get_contents()->dir_rmr();
   }
   else if (words[1].compare("..") == 0)
   {
   	throw command_error (words[0] + ": Invalid Argument! Cannot delete parent directory.");
      exec::status(1);
   }
   else if (words[1].compare("/") == 0)
   {
   	state.set_cwd(state.get_root());
   	state.get_cwd()->get_contents()->dir_rmr();
   }
   else
   {
   	// CASE: pathname
   	int start_root = 0;
	   string rooted = words[1];
	   if(rooted[0] == '/') start_root = 1;
	   inode_ptr temp;
	   wordvec isolate = split(words[1],"/");
	   // CASE: "rmr (/test)" "rmr (/a/aa/aaa)"
	   if(start_root)
	   {
	   	temp = state.get_cwd()->get_contents()->valid_pathName(state.get_root(),isolate,0);
	   }
	   // CASE: "rmr (test)" "rmr (a/aa/aaa)"
	   else
	   {
	   	temp = state.get_cwd()->get_contents()->valid_pathName(state.get_cwd(),isolate,0);
	   }
	   if(temp == nullptr)
	   {
	      // return error and exit
	      throw command_error (words[0] + ": Directory path does not exist.");
	      exec::status(1);
	   }
   	temp->get_contents()->dir_rmr();
   }
}