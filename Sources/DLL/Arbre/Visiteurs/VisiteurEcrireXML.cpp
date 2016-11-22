//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author Loic Sauvageau
/// @date 2014-11-01
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "VisiteurEcrireXML.h"

void VisiteurEcrireXML::visite(NoeudAbstrait* objet)
{
	/// sauvegarde du type
	fils = new TiXmlElement("type");
	fils->LinkEndChild(new TiXmlText(objet->obtenirType().c_str()));
	pere->LinkEndChild(fils);

	/// sauvegarde position relative
	fils = new TiXmlElement("position_relative");
	pere->LinkEndChild(fils);
	fils->SetDoubleAttribute("x", objet->obtenirPositionRelative()[0]);
	fils->SetDoubleAttribute("y", objet->obtenirPositionRelative()[1]);
	fils->SetDoubleAttribute("z", objet->obtenirPositionRelative()[2]);

	/// sauvegarde taille relative
	fils = new TiXmlElement("taille_relative");
	pere->LinkEndChild(fils);
	fils->SetDoubleAttribute("x", objet->obtenirTailleRelative()[0]);
	fils->SetDoubleAttribute("y", objet->obtenirTailleRelative()[1]);
	fils->SetDoubleAttribute("z", objet->obtenirTailleRelative()[2]);

	/// sauvegarde angle rotation
	fils = new TiXmlElement("angle_rotation");
	pere->LinkEndChild(fils);
	fils->SetDoubleAttribute("angle", objet->obtenirAngleRotation());
}

void VisiteurEcrireXML::initialiseXML()
{
	/// On nettoie le document pour le réutilise
	docXML.Clear();

	/// On génère l'entête du document 
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	docXML.LinkEndChild(decl);

	/// On crée le noeud principal
	racine = new TiXmlElement("Billard");



}

void VisiteurEcrireXML::ecritureXML(ArbreRenduINF2990 * arbre)
{
	/// On prend le noeud du tablier
	if (arbre->obtenirNombreEnfants() > 0)
	{
		TiXmlElement *noeudTablier = new TiXmlElement("Noeud_Tablier");

		/// point zone suivante
		fils = new TiXmlElement("cote_difficulte");
		racine->LinkEndChild(fils);
		fils->SetAttribute("cote", arbre->obtenirDifficulte());

		/// point zone suivante
		fils = new TiXmlElement("points_zone_suivante");
		racine->LinkEndChild(fils);
		fils->SetAttribute("point", arbre->obtenirPointsCampagne());

		/// point bille gratuite
		fils = new TiXmlElement("points_bille_gratuite");
		racine->LinkEndChild(fils);
		fils->SetAttribute("point", arbre->obtenirPointsBille());

		/// point butoir circulaire
		fils = new TiXmlElement("points_butoir_circulaire");
		racine->LinkEndChild(fils);
		fils->SetAttribute("point", arbre->obtenirPointsCollision(ArbreRenduINF2990::NOM_BUTOIR_CIRCULAIRE));

		/// point bille gratuite
		fils = new TiXmlElement("points_butoir_triangulaire");
		racine->LinkEndChild(fils);
		fils->SetAttribute("point", arbre->obtenirPointsCollision(ArbreRenduINF2990::NOM_BUTOIR_TRIANGULAIRE_DROIT));

		/// point bille gratuite
		fils = new TiXmlElement("points_cible");
		racine->LinkEndChild(fils);
		fils->SetAttribute("point", arbre->obtenirPointsCollision(ArbreRenduINF2990::NOM_CIBLE));

		traverseNoeudRecursif(arbre->chercher(0), noeudTablier);
		racine->LinkEndChild(noeudTablier);
		docXML.LinkEndChild(racine);
	}

}


void VisiteurEcrireXML::traverseNoeudRecursif(NoeudAbstrait* noeud, TiXmlElement* noeudSuperieur)
{
	if (noeud != nullptr)
	{
		pere = noeudSuperieur;
		noeud->accepte(this);

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); ++i)
		{
			if (noeud->chercher(i)->obtenirType() != ArbreRenduINF2990::NOM_BILLE)
			{
				TiXmlElement *noeudSecondaire = new TiXmlElement("Noeud");
				traverseNoeudRecursif(noeud->chercher(i), noeudSecondaire);
				noeudSuperieur->LinkEndChild(noeudSecondaire);
			}
		}
	}
}

void VisiteurEcrireXML::sauvegardeXML(std::string nomFichier)
{
	docXML.SaveFile(nomFichier.c_str());
}