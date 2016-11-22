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
    /// Etat qui s'occupe d'effectuer les zoom
    /// </summary>
    class ZoomState : AbstractState
    {
        public override void Action(int x, int y)
        {

        }

        /// <summary>
        /// Fonction pour le zoom in dans le rectangle elastique
        /// </summary>
        /// <param name="minX">x de gauche du rectangle</param>
        /// <param name="minY">y du bas du rectangle</param>
        /// <param name="maxX">x de droite du rectangle</param>
        /// <param name="maxY">y du haut du rectangle</param>
        public void zoomInRect(int minX, int minY, int maxX, int maxY)
        {
            FonctionsNatives.ZoomInRectangle(minX, minY, maxX, maxY);
        }

        /// <summary>
        /// Fonction pour le zoom out dans le rectangle elastique
        /// </summary>
        /// <param name="minX">x de gauche du rectangle</param>
        /// <param name="minY">y du bas du rectangle</param>
        /// <param name="maxX">x de droite du rectangle</param>
        /// <param name="maxY">y du haut du rectangle</param>
        public void zoomOutRect(int minX, int minY, int maxX, int maxY)
        {
            FonctionsNatives.ZoomOutRectangle(minX, minY, maxX, maxY);
        }
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ZoomInRectangle(int minX, int minY, int maxX, int maxY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ZoomOutRectangle(int minX, int minY, int maxX, int maxY);
    }
}
