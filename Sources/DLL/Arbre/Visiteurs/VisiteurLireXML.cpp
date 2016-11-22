//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author Loic Sauvageau
/// @date 2014-11-01
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "VisiteurLireXML.h"
#include "Utilitaire.h"


VisiteurLireXML::VisiteurLireXML()
{
	docXML = nullptr;
	hdoc = nullptr;
}

VisiteurLireXML::~VisiteurLireXML()
{
	if (docXML != nullptr)
		delete docXML;
	docXML = nullptr;

	if (hdoc != nullptr)
		delete hdoc;
	hdoc = nullptr;

}

void VisiteurLireXML::visite(NoeudAbstrait* objet)
{
	double elementX, elementY, elementZ, angle;

	/// Assigner la position relative du noeud
	pere->FirstChildElement("position_relative")->QueryDoubleAttribute("x", &elementX);
	pere->FirstChildElement("position_relative")->QueryDoubleAttribute("y", &elementY);
	pere->FirstChildElement("position_relative")->QueryDoubleAttribute("z", &elementZ);
	const glm::dvec3 position(elementX, elementY, elementZ);
	objet->assignerPositionRelative(position);

	/// Assigner la taille relative du noeud
	pere->FirstChildElement("taille_relative")->QueryDoubleAttribute("x", &elementX);
	pere->FirstChildElement("taille_relative")->QueryDoubleAttribute("y", &elementY);
	pere->FirstChildElement("taille_relative")->QueryDoubleAttribute("z", &elementZ);
	objet->assignerScale(elementX, elementY, elementZ);

	/// Assigner la rotation du noeud
	pere->FirstChildElement("angle_rotation")->QueryDoubleAttribute("angle", &angle);
	objet->assignerAngleRotation(angle);
}

bool VisiteurLireXML::ouvrirXML(char* nomFichier)
{
	/// Lecture du fichier XML
	docXML = new TiXmlDocument(nomFichier);
	if (!docXML->LoadFile())
		return false;

	/// Sauvegarde de la racine du fichier XML
	hdoc = new TiXmlHandle(docXML);
	
	/// Vérifie l'intégralité du noeud du tablier
	pere = hdoc->FirstChildElement().FirstChildElement().Element();

	if (!pere)
		return false;

	return true;
}

bool  VisiteurLireXML::parcourirXML()
{
	numeroPortail = 0;
	int temp = 0;

	pere = hdoc->FirstChildElement().FirstChildElement("cote_difficulte").Element();
	pere->QueryIntAttribute("cote", &temp);
	noeudArbre->assignerDifficulte(temp);

	pere = hdoc->FirstChildElement().FirstChildElement("points_zone_suivante").Element();
	pere->QueryIntAttribute("point", &temp);
	noeudArbre->assignerPointsCampagne(temp);

	pere = hdoc->FirstChildElement().FirstChildElement("points_bille_gratuite").Element();
	pere->QueryIntAttribute("point", &temp);
	noeudArbre->assignerPointsBille(temp);

	pere = hdoc->FirstChildElement().FirstChildElement("points_butoir_circulaire").Element();
	pere->QueryIntAttribute("point", &temp);
	noeudArbre->assignerPointsButoirCir(temp);

	pere = hdoc->FirstChildElement().FirstChildElement("points_butoir_triangulaire").Element();
	pere->QueryIntAttribute("point", &temp);
	noeudArbre->assignerPointsButoirTri(temp);

	pere = hdoc->FirstChildElement().FirstChildElement("points_cible").Element();
	pere->QueryIntAttribute("point", &temp);
	noeudArbre->assignerPointsCible(temp);
	
	pere = hdoc->FirstChildElement().FirstChildElement("Noeud_Tablier").Element();
	const std::string nomNoeud = pere->FirstChildElement("type")->GetText();
	NoeudAbstrait* noeud{ noeudArbre->creerNoeud(nomNoeud) };
	noeudArbre->ajouter(noeud);
	noeud->accepte(this);

	pere = pere->FirstChildElement("Noeud");
	for (pere; pere; pere = pere->NextSiblingElement())
	{
		const std::string noeudSecondaire = pere->FirstChildElement("type")->GetText();
		noeud = noeudArbre->ajouterNouveauNoeud(nomNoeud, noeudSecondaire);
		noeud->accepte(this);

		if (noeudSecondaire == "portail")
		{
			((NoeudPortail*)noeud)->assignerId(numeroPortail);
			pere = pere->NextSiblingElement();
			noeud = noeudArbre->ajouterNouveauNoeud(nomNoeud, noeudSecondaire);
			noeud->accepte(this);
			((NoeudPortail*)noeud)->assignerId(numeroPortail);
			++numeroPortail;
		}
	}

	return true;
}

bool  VisiteurLireXML::verifieXML()
{

	pere = hdoc->FirstChildElement().FirstChildElement("Noeud_Tablier").Element();

	/// on insère le tablier dans l'arbre
	if (pere->FirstChildElement("type") == nullptr)
		return false;

	/// vérifie les noeuds de la table
	pere = pere->FirstChildElement("Noeud");
	for (pere; pere; pere = pere->NextSiblingElement())
	{
		if (pere->FirstChildElement("type") == nullptr)
			return false;

		if (pere->FirstChildElement("type")->GetText() == "portail")
		{
			pere = pere->NextSiblingElement();
			if (pere->FirstChildElement("type") == nullptr)
				return false;
			else if (pere->FirstChildElement("type")->GetText() != "portail")
				return false;
		}
	}

	return true;
}
/////////////////////////////////////////////////////////
/// @fn int VisiteurLireXML::obtenirDifficulteXML()
///
/// Cette fonction vas chercher l'attribut difficulte dans le xml
/// 
///
/// @return int : la difficulte de la zone
///
////////////////////////////////////////////////////////////////////////
int VisiteurLireXML::obtenirDifficulteXML()
{
		int difficulte = 0;
		pere = hdoc->FirstChildElement().FirstChildElement("cote_difficulte").Element();
		pere->QueryIntAttribute("cote", &difficulte);
		return difficulte;
}

