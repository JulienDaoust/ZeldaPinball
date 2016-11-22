///////////////////////////////////////////////////////////////////////////
/// @file VisiteurLireXML.h
/// @author Francois
/// @date 2014-09-19
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __VISITEUR_ECRIRE_XML_H__
#define __VISITEUR_ECRIRE_XML_H__


#include "VisiteurAbstrait.h"
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
	void ecritureXML(NoeudAbstrait* objet);

	/// fonction récursive
	void traverseNoeudRecursif(NoeudAbstrait* noeud, TiXmlElement* noeudSuperieur);

private:
	TiXmlDocument docXML;
	TiXmlElement *racine;
	TiXmlElement *pere;
	TiXmlElement *fils;

};

#endif