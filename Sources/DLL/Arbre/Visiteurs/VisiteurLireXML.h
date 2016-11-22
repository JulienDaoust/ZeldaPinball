///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurLire.h
/// @author Loïc Sauvageau
/// @date 2014-08-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEUR_LIRE_XML_H__
#define __VISITEUR_LIRE_XML_H__


#include "VisiteurAbstrait.h"
#include "ArbreRenduINF2990.h"
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
	
	int obtenirDifficulteXML();

	void assignerPointeurArbre(ArbreRenduINF2990 *noeudArbre)
	{
		this->noeudArbre = noeudArbre;
	}

private:
	TiXmlDocument *docXML;
	TiXmlHandle *hdoc;
	TiXmlElement *pere;
	TiXmlElement *fils;

	int numeroPortail;
	ArbreRenduINF2990 *noeudArbre;
};

#endif