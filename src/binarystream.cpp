/*
 * Copyright (C) 2017  Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "binarystream.h"
#include "belr/belr.h"
#include <netinet/in.h>

using namespace std;

namespace belr{

/**
 * The BinaryInputStream is used internally to read grammars from a binary file.
**/
int BinaryInputStream::readInt(){
	int tmp = 0;
	read((char*)&tmp, sizeof(tmp));
	return ntohl(tmp);
}

unsigned char BinaryInputStream::readUChar(){
	unsigned char ret = 0;
	read((char*)&ret, 1);
	return ret;
}

std::string BinaryInputStream::readString(){
	string ret;
	unsigned char c;
	while (good()){
		read((char*)&c, 1);
		if (c != '\0') ret.push_back(c);
		else break;
	}
	return ret;
}

BinaryGrammarBuilder::BinaryGrammarBuilder(Grammar &grammar) : mGrammar(grammar){
}

std::shared_ptr<Recognizer> BinaryGrammarBuilder::getRule(const string &name){
	return mGrammar.getRule(name);
}


void BinaryOutputStream::writeInt(int val){
	int tmp = htonl(val);
	write((char*)&tmp, sizeof(tmp));
}


void BinaryOutputStream::writeUChar(unsigned char val){
	write((char*)&val, 1);
}

void BinaryOutputStream::writeString(const string &val){
	write((char*)val.c_str(), val.size() + 1); //because we want to write the null byte.
}





}//end of namespace


