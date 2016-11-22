using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

namespace InterfaceGraphique.patron_state
{
    /// <summary>
    /// Etat pour la suppression d'un objet
    /// </summary>
    class DeletionState : AbstractState
    {
        /// <summary>
        /// On supprime les objets selectionnes
        /// </summary>
        /// <param name="x">Ne sert a rien pour la suppression puisqu'on supprime les objets selectionnes</param>
        /// <param name="y">Ne sert a rien ici aussi</param>
        public override void Action(int x, int y)
        {
            FonctionsNatives.supprimerObjets();
        }
    }

    static partial class FonctionsNatives
    {
      
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerObjets();
    }
}
