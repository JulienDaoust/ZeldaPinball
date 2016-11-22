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

	/// sauvegarde multiplicateur scale
	fils = new TiXmlElement("multiplicateur");
	pere->LinkEndChild(fils);
	fils->SetDoubleAttribute("multi", objet->obtenirMultiplicateur());

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

void VisiteurEcrireXML::ecritureXML(NoeudAbstrait * arbre)
{
	/// On prend le noeud du tablier
	if (arbre->obtenirNombreEnfants() > 0)
	{
		TiXmlElement *noeudTablier = new TiXmlElement("Noeud_Tablier");
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

		for (int i = 0; i < noeud->obtenirNombreEnfants(); ++i)
		{
			TiXmlElement *noeudSecondaire = new TiXmlElement("Noeud");
			traverseNoeudRecursif(noeud->chercher(i), noeudSecondaire);
			noeudSuperieur->LinkEndChild(noeudSecondaire);
		}
	}
}

void VisiteurEcrireXML::sauvegardeXML(std::string nomFichier)
{
	docXML.SaveFile(nomFichier.c_str());
}