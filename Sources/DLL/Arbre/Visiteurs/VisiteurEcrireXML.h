///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurEcrireXml.h
/// @author Lo�c Sauvageau
/// @date 2014-08-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEUR_ECRIRE_XML_H__
#define __VISITEUR_ECRIRE_XML_H__


#include "VisiteurAbstrait.h"
#include "../ArbreRenduINF2990.h"
#include "tinyxml.h"
#include <iostream>
#include <string>

class VisiteurEcrireXML : public VisiteurAbstrait
{
public:
	VisiteurEcrireXML() {}
	virtual ~VisiteurEcrireXML() {}

	/// rajoute un noeud au XML
	virtual void visite(NoeudAbstrait* objet);

	/// d�marre le processus de cr�ation du XML
	void initialiseXML();

	/// sauvegarde le xml
	void sauvegardeXML(std::string nomFichier);

	/// d�marre r�cursion pour prendre le noeud de l'arbre
	void ecritureXML(ArbreRenduINF2990* objet);

	/// fonction r�cursive
	void traverseNoeudRecursif(NoeudAbstrait* noeud, TiXmlElement* noeudSuperieur);

private:
	TiXmlDocument docXML;
	TiXmlElement *racine;
	TiXmlElement *pere;
	TiXmlElement *fils;

};

#endif