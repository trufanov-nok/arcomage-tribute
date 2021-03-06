/*
 * Arcomage Tribute
 *
 * File: 	config.cpp
 * Desc: 	Provides functions to read configuration data from
 *			XML files.
 *
 * Date: 	10/2007
 *
 * Copyright (C) 2007 - 2010 Xography. <www.gatewayheaven.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "config.h"

static const std::string default_config( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\
                                         <Configuration>\
                                                 <screen x=\"1024\" y=\"768\" depth=\"32\" fullscreen=\"0\" /> \
                                                 <sound enabled=\"1\" />\
                                                 <audio rate=\"44100\" channels=\"2\" buffers=\"4096\" />\
                                                 <effects volume=\"15\" />\
                                                 <music volume=\"25\" />\
                                                 <intro display=\"1\" />\
                                         </Configuration>");

namespace arcomage {

	// -------------------------------------------------------------------------
	// read an integer from a xml file
	int Config::readInteger(const char* child,
		const char* attribute,
		const char* file)
	{
        TiXmlDocument doc(file);

        if (!doc.LoadFile()) {
        //Utility::getInstance()->exitError("Failed to load config file");
        doc.Parse(default_config.c_str());
        }
		int val = 0;

		TiXmlElement* root = doc.RootElement();
		TiXmlElement* tmp;
		tmp = root->FirstChildElement(child);
		tmp->Attribute(attribute, &val);

		return val;
	}

	// -------------------------------------------------------------------------
	// read a string from a xml file
	const char* Config::readString(const char* child,
		const char* attribute,
		const char* file)
	{
		TiXmlDocument doc(file);

        if (!doc.LoadFile()) {
        //Utility::getInstance()->exitError("Failed to load config file");
        doc.Parse(default_config.c_str());
        }
		const char* temp;

		TiXmlElement* root = doc.RootElement();
		TiXmlElement* tmp;
		tmp = root->FirstChildElement(child);
		temp = tmp->Attribute(attribute);
		return temp;
	}
}
