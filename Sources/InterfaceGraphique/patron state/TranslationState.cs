using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Drawing;

namespace InterfaceGraphique.patron_state
{
    /// <summary>
    /// Etat qui fait la translation
    /// </summary>
    class TranslationState : AbstractState
    {
        /// <summary>
        /// On definit la position du premier clique
        /// </summary>
        /// <param name="x">position en x du premier clique</param>
        /// <param name="y">position en y du premier clique</param>
        public void setLastPos(int x, int y)
        {
            lastPos = new Point(x, y);
        }

        /// <summary>
        /// Fonction qui effectue la translation sur les objets selectionnes
        /// </summary>
        /// <param name="x">position courante en x de la souris</param>
        /// <param name="y">position courante en y de la souris</param>
        public override void Action(int x, int y)
        {
            if (lastPos.X != 0 && lastPos.Y !=0)
            {
                FonctionsNatives.translation(lastPos.X, lastPos.Y, x, y);
                lastPos = new Point(x, y);
            }
        }

        /// <summary>
        /// Fonction utilise pour faire une translation en x avec l'affiche de propriete
        /// </summary>
        /// <param name="x">translation en x</param>
        public void translationX(int x)
        {
            FonctionsNatives.translationX(x);
        }

        /// <summary>
        /// Fonction utilise pour faire une translation en y avec l'affiche de propriete
        /// </summary>
        /// <param name="x">translation en y</param>
        public void translationY(int y)
        {
            FonctionsNatives.translationY(y);
        }

        /// <summary>
        /// Dernier point de la souris
        /// </summary>
        private Point lastPos;
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translation(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translationX(int x);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translationY(int y);
    }
}
