///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPORTAIL_H__
#define __ARBRE_NOEUDS_NOEUDPORTAIL_H__


#include "NoeudComposite.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudPortail
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudPortail : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudPortail(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudPortail();

   /// permet d'activer/deactiver lemode debug
   inline void assignerDebug(bool debug);
   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   /// Accepte le Visiteur
   virtual void accepte(VisiteurAbstrait* Visiteur);

   /// Assigne un frere au portail
   virtual void assignerFrere(NoeudPortail* noeud);

   ///  retourne le rayon du plus petits cercle contenant l'objet (avec champ attraction)
   virtual double calculerRayon() const;

   ///  retourne le rayon du plus petits cercle contenant l'objet
   double calculerRayonPortail() const;

   /// Obtient le frere du portail
   virtual NoeudPortail* obtenirFrere();

   //Assigne une valeur d'identifiant au portail(la meme pour une paire)
   virtual void assignerId(int id);

   //Obtenir l'Id du portail
   virtual int obtenirId();

   /// permet d'identifier les collisions
   virtual aidecollision::DetailsCollision collision(NoeudAbstrait* noeud);

private:
   /// Portail lié
   NoeudPortail* portailFrere;

   /// Angle dans le sinus de l'oscillation
   float angle_{ 0 };

   /// Identifiant du portail
   int portailId_;

   /// champ d'attaction
   double modifierChampAttraction_{ 3.0 };

   // Varibale pour mode debug
   bool modeDebug_ = false;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudPortail::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudPortail::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudPortail::obtenirFrere()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline NoeudPortail* NoeudPortail::obtenirFrere()
{
	return portailFrere;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudPortail::assignerId(int id)
///
/// Cette fonction permet d'assigner un Id a une paire de portail
///
/// @param[in] id : identifiant de la paire
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudPortail::assignerId(int id)
{
	portailId_ = id;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int NoeudPortail::obtenirId()
///
/// Cette fonction permet d'assigner un Id a une paire de portail
///
/// @return Valeur de l'identifiant
///
////////////////////////////////////////////////////////////////////////
inline int NoeudPortail::obtenirId()
{
	return portailId_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudPortail::assignerDebug()
///
/// Cette fonction permet d'activer/desactiver le mode debug
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudPortail::assignerDebug(bool debug)
{
	modeDebug_ = debug;
}

#endif // __ARBRE_NOEUDS_NOEUDPORTAIL_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
