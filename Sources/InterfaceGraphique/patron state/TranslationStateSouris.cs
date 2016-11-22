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
    /// Etat qui s'soccupe de faire une translation avec la souris
    /// </summary>
    class TranslationStateSouris : AbstractState
    {
        /// <summary>
        /// Assigne la derniere position de la souris
        /// </summary>
        /// <param name="x">Derniere position en x</param>
        /// <param name="y">Derniere position en y</param>
        public void setLastPos(int x, int y)
        {
            lastPos = new Point(x, y);
        }

        /// <summary>
        /// On effectue la translation des objets selectionnes
        /// </summary>
        /// <param name="x">position en x de la souris</param>
        /// <param name="y">position en y de la souris</param>
        public override void Action(int x, int y)
        {
            if (lastPos.X != 0 && lastPos.Y !=0)
            {
                FonctionsNatives.translationSouris(lastPos.X, lastPos.Y, x, y);
                lastPos = new Point(x, y);
            }
        }

        /// <summary>
        /// Derniere position de la souris
        /// </summary>
        private Point lastPos;
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translationSouris(int x1, int y1, int x2, int y2);
    }
}
