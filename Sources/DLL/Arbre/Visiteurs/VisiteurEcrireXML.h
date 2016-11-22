///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurEcrireXml.h
/// @author Loïc Sauvageau
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

	/// démarre le processus de création du XML
	void initialiseXML();

	/// sauvegarde le xml
	void sauvegardeXML(std::string nomFichier);

	/// démarre récursion pour prendre le noeud de l'arbre
	void ecritureXML(ArbreRenduINF2990* objet);

	/// fonction récursive
	void traverseNoeudRecursif(NoeudAbstrait* noeud, TiXmlElement* noeudSuperieur);

private:
	TiXmlDocument docXML;
	TiXmlElement *racine;
	TiXmlElement *pere;
	TiXmlElement *fils;

};

#endif