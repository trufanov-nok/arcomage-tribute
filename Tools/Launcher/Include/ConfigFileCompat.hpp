#ifndef _ConfigFileCompat_h_
#define _ConfigFileCompat_h_
#include <map>
#include <string>
#include <fstream>
#include <QDir>

#include "SAXHandler.h"
#include "SAXParser.h"

#include <boost/lexical_cast.hpp>

static const std::string default_config( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\
                                         <Configuration>\
                                                 <screen x=\"1024\" y=\"768\" depth=\"32\" fullscreen=\"0\" /> \
                                                 <sound enabled=\"1\" />\
                                                 <audio rate=\"44100\" channels=\"2\" buffers=\"4096\" />\
                                                 <effects volume=\"15\" />\
                                                 <music volume=\"25\" />\
                                                 <intro display=\"1\" />\
                                         </Configuration>");

using namespace Aeon;

class ConfigFileCompat : public SAXHandler  {
private:

	std::string filename;
	std::map<const std::string, int> configuration;
public:

	// -------------------------------------------------------------------------
	void store(const std::string& file) {
            QString fname;
            QDir dir(QDir::homePath());
            if(dir.exists("/usr/share/games/ArcomageTribute/"))
            {
                // deb installation
                dir.mkpath(".config/ArcomageTribute/");
                fname = QDir::cleanPath(dir.absolutePath()) + "/.config/ArcomageTribute/";
            }
            else {
                // simple launch
                fname = "data/";
            }
                std::ofstream out(fname.append(file.c_str()).toStdString());

		out << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl << std::endl
			<< "<Configuration>" << std::endl
			<< "\t<screen "
			<< "x=\"" << configuration["screen x"] << "\" "
			<< "y=\"" << configuration["screen y"] << "\" "
			<< "depth=\"" << configuration["screen depth"] << "\" "
			<< "fullscreen=\"" << configuration["screen fullscreen"] << "\" /> " << std::endl
			<< "\t<sound "
			<< "enabled=\"" << configuration["audio enabled"] << "\" />" << std::endl
			<< "\t<audio "
			<< "rate=\"" << configuration["audio rate"]  << "\" "
			<< "channels=\"" << configuration["audio channels"] << "\" " 
			<< "buffers=\"" << configuration["audio buffers"]  << "\" />" << std::endl
			<< "\t<effects volume=\"" << configuration["effects volume"] << "\" />" << std::endl
			<< "\t<music volume=\"" << configuration["music volume"] << "\" />" << std::endl
			<< "\t<intro display=\"" << configuration["splash enabled"]  << "\" />" << std::endl
			<< "</Configuration>" << std::endl;

		out.close();
	}

	// -------------------------------------------------------------------------
	bool load(const std::string& file) {
		SAXParser parser(this);

                QString fname;
                QDir dir(QDir::homePath());
                if(dir.exists("/usr/share/games/ArcomageTribute/"))
                {
                    // deb installation
                    dir.mkpath(".config/ArcomageTribute/");
                    fname = QDir::cleanPath(dir.absolutePath()) + "/.config/ArcomageTribute/";
                }
                else {
                    // simple launch
                    fname = "data/";
                }

		try {
                        if (parser.parse(fname.append(file.c_str()).toStdString())) {
                            return true;
                        }
                        else {
                           parser.parseString(default_config);
                           return true;
                        }
		} catch(Aeon::SAXParserException& e) {                    
                   parser.parseString(default_config);
                   return true;
		}
          return false;
	}

	// -------------------------------------------------------------------------
	void setValue(const std::string& key, int value) {
		configuration[key] = value;
	}

	// -------------------------------------------------------------------------
	int getValue(const std::string& key) {
		return configuration[key];
	}

protected:
	int toInt(const std::string& str) {
		try {
			return(!str.empty() ? boost::lexical_cast<int>(str) : 0);
		} catch(boost::bad_lexical_cast) {
			return 0;
		} 
	}

	// Used methods from SAXAdapter
	void startElement(const XMLString& name, 
		const XMLAttributes& attributes) {
		if(name == "screen") {
			configuration["screen x"] = toInt(attributes.get("x"));
			configuration["screen y"] = toInt(attributes.get("y"));
			configuration["screen depth"] = toInt(attributes.get("depth"));
			configuration["screen fullscreen"] =   toInt(attributes.get("fullscreen"));
		} else if(name == "sound") {
			configuration["audio enabled"] = toInt(attributes.get("enabled"));
		} else if(name == "audio") {
			configuration["audio rate"] = toInt(attributes.get("rate"));
			configuration["audio channels"] = toInt(attributes.get("channels"));
                        configuration["audio buffers"] = toInt(attributes.get("buffers"));
		} else if(name == "effects") {
			configuration["effects volume"] = toInt(attributes.get("volume"));
		} else if(name == "music") {
			configuration["music volume"] = toInt(attributes.get("volume"));
		}  else if(name == "intro") {
			configuration["splash enabled"] = toInt(attributes.get("display"));
		}
	}
		
	void endElement(const XMLString& name) { }

	void characterData(const XMLString &data) { }
};
#endif
