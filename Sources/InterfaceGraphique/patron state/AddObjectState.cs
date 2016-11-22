using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace InterfaceGraphique.patron_state
{
    /// <summary>
    /// Etat d'ajout des objets
    /// </summary>
    class AddObjectState : AbstractState
    {
        /// <summary>
        /// Variable reprensentant la position en x du premier clique
        /// </summary>
        int firstClickX;
        /// <summary>
        /// Variable representant la position en y du premier clique
        /// </summary>
        int firstClickY;
        /// <summary>
        /// Vairaible qui indique s'il y a bien eu un seul clique 
        /// </summary>
        bool firstClick = true;
        /// <summary>
        /// Type d'objet que l'on veut creer
        /// </summary>
        String objectType;

        /// <summary>
        /// Constructeur de l'etat, assigne le type de noeud a ajouter
        /// </summary>
        /// <param name="objectName">Type de noeud</param>
        public AddObjectState(String objectName)
        {
            objectType = objectName;
            //TODO:  changer la couleur des ribbon nuttons selon l'object name
        }

        /// <summary>
        /// Creation du noeud et ajout dans l'arbre de rendu
        /// </summary>
        /// <param name="x">Position courante du x de la souris</param>
        /// <param name="y">Positinn y courante de la souris</param>
        public override void Action(int x, int y)
        {
            
            //Création d'un Noeud
            if (objectType != null && objectType != ModeEditeur.NOM_PORTAIL && objectType != ModeEditeur.NOM_MUR)
            {
                FonctionsNatives.ajouterNoeud(objectType.ToCharArray(0, objectType.Length), x, y);
                firstClick = true;
            }

            ///Création d'un Noeud Portail partieRapide 1
            else if ((objectType == ModeEditeur.NOM_PORTAIL || objectType == ModeEditeur.NOM_MUR) && firstClick)
            {
                firstClickX = x;
                firstClickY = y;
                firstClick = false;
            }
            ///Création d'un Noeud Portail partieRapide 2
            else if (objectType == ModeEditeur.NOM_PORTAIL && !firstClick)
            {
                FonctionsNatives.ajouterNoeudPortail(firstClickX, firstClickY, x, y);
                firstClick = true;
            }
            ///Création d'un Noeud Mur partieRapide 1
            else if (objectType == ModeEditeur.NOM_MUR && !firstClick)
            {
                FonctionsNatives.ajouterNoeudMur(firstClickX, firstClickY, x, y);
                firstClick = true;
            }
        }
    }

    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterNoeud(char[] nom, int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterNoeudMur(int x1, int y1, int x2, int y2);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterNoeudPortail(int x1, int y1, int x2, int y2);
    }
}
