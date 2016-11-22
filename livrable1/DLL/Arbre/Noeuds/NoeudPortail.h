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

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   /// Accepte le Visiteur
   virtual void accepte(VisiteurAbstrait* Visiteur);

   /// Assigne un frere au portail
   virtual void assignerFrere(NoeudPortail* noeud);

   /// Obtient le frere du portail
   virtual NoeudPortail* obtenirFrere();

   //Assigne une valeur d'identifiant au portail(la meme pour une paire)
   virtual void assignerId(int id);

   //Obtenir l'Id du portail
   virtual int obtenirId();


private:
   /// Portail lié
   NoeudPortail* portailFrere;

   /// Angle dans le sinus de l'oscillation
   float angle_{ 0 };

   /// Identifiant du portail
   int portailId_;

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

#endif // __ARBRE_NOEUDS_NOEUDPORTAIL_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
