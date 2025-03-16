#pragma once

#include "LIST.h"
#include <string>
#include "MonPol.h"

template <typename key,typename val>
struct pair
{
	key keyl;
	val valm;
	pair(key _keyl, val _valm)
	{
		keyl = _keyl;
		valm = _valm;
	}
};
template <typename key, typename val>
class Tabloid
{
	int nRec; // table size
	LIST<pair<key, val>>* Placeholder;
public:
	//constructors
	// table-listed
	Tabloid(int _nRec = 1) : nRec(_nRec)
	{		
		if (nRec < 1)
		{
			throw "table cannot be empty";
		}
		Placeholder = new LIST<pair<key, val>>();
		List Nullpolynym = new List();
		for (int i = 0;i<nRec;i++)
		{
			Placeholder.InsertLast(pair("XVAL" + std::to_string(i)),Nullpolynym);
		}
	}
	// redn'black tree
	//Tabloid();
	// hash-tash
	//Tabloid(); 
	//destructors
	~Tabloid() //table-listed
	{
		delete Placeholder;
		nRec = 1;
	}
	//~Tabloid(); //redn'black tree
	//~Tabloid(); //hash-tash
	//table-listed
	void Insert(key& keyl, val& vall)
	{
		bool allow = false;
		for (int i = 0;i<nRec;i++)
		{
			if ("XVAL" + std::to_string(i) == keyl)
			{
				allow = true;
				break;
			}
		}
		if (allow)
		{
			
		}
	}
	virtual void Delete(key& keyl);
	virtual val Search(key& keyl);
	//redn'black tree
	//hash-tash
};