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

	/// d�marre le processus de cr�ation du XML
	void initialiseXML();

	/// sauvegarde le xml
	void sauvegardeXML(std::string nomFichier);

	/// d�marre r�cursion pour prendre le noeud de l'arbre
	void ecritureXML(NoeudAbstrait* objet);

	/// fonction r�cursive
	void traverseNoeudRecursif(NoeudAbstrait* noeud, TiXmlElement* noeudSuperieur);

private:
	TiXmlDocument docXML;
	TiXmlElement *racine;
	TiXmlElement *pere;
	TiXmlElement *fils;

};

#endif