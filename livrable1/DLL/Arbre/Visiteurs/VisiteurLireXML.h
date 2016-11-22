///////////////////////////////////////////////////////////////////////////
/// @file VisiteurLireXML.h
/// @author Francois
/// @date 2014-09-19
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __VISITEUR_LIRE_XML_H__
#define __VISITEUR_LIRE_XML_H__


#include "VisiteurAbstrait.h"
#include "ArbreRendu.h"
#include "NoeudPortail.h"
#include "tinyxml.h"
#include <iostream>
#include <string>

class VisiteurLireXML : public VisiteurAbstrait
{
public:
	VisiteurLireXML();
	virtual ~VisiteurLireXML();

	/// rajoute un noeud au XML
	virtual void visite(NoeudAbstrait* objet);

	bool ouvrirXML(char* nomFichier);

	bool parcourirXML();

	bool verifieXML();
	
	void assignerPointeurArbre(ArbreRendu *noeudArbre)
	{
		this->noeudArbre = noeudArbre;
	}

private:
	TiXmlDocument *docXML;
	TiXmlHandle *hdoc;
	TiXmlElement *pere;
	TiXmlElement *fils;

	int numeroPortail;
	ArbreRendu *noeudArbre;
};

#endif