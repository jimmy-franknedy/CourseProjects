// $Id: listmap.tcc,v 1.15 2019-10-30 12:44:53-07 - - $

#include "listmap.h"
#include "debug.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename key_t, typename mapped_t, class less_t>
listmap<key_t,mapped_t,less_t>::~listmap() {
   DEBUGF ('l', reinterpret_cast<const void*> (this));
   while(begin() != end()) erase(begin());
}

//
// iterator listmap::insert (const value_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::insert (const value_type& pair) {
   DEBUGF ('l', &pair << "->" << pair);
   node* n;
   if(empty())
   {
   	n = new node(anchor(),anchor(),pair);
   	anchor()->next = n;
   	anchor()->prev = n;
   	return n;
   }
   else
   {
   	auto index = find(pair.first);
   	if(index == end())
   	{
   		// cout << "ended" << endl;
   		index = begin();
   		while(index != end())
   		{
   			if(less(pair.first,index->first))
   			{
   				n = new node(index.where,index.where->prev,pair);
   				index.where->prev->next = n;
   				index.where->prev = n;
   				// cout << "added a NEW node" << endl;
   				return index;
   			}
   			++index;
   		}
   		n = new node(anchor(),anchor()->prev,pair);
   		anchor()->prev->next = n;
   		anchor()->prev = n;
   		// cout << "added a NEW node @ the anchor" << endl;
   		return index;
   	}
   	else
   	{
   		(*index).second = pair.second;
   		// cout << "replacing the value!" << endl;
   		return index;
   	}
   }
}

//
// listmap::find(const key_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::find (const key_type& that) {
   DEBUGF ('l', that);
   auto index = begin();
   while(index != end())
   {
   	if(!less(index->first,that) && !(less(that,index->first))) break;
   	++index;
   }
   return index;
}

//
// iterator listmap::erase (iterator position)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::erase (iterator position) {
   DEBUGF ('l', &*position);
   auto index = position;
   if(position != end())
   {
   	index.where->prev->next = index.where->next;
   	index.where->next->prev = index.where->prev;
   	delete(index.where);
   }
   return end();
}