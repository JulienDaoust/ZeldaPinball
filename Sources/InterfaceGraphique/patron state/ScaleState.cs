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
    /// Outil de mise a l'echelle
    /// </summary>
    class ScaleState : AbstractState
    {
        /// <summary>
        /// On effectue une mise a l'echelle
        /// </summary>
        /// <param name="x">Position en x de la souris</param>
        /// <param name="y">Position en y de la souris</param>
        public override void Action(int x, int y)
        {
            FonctionsNatives.scaling(x, y);
        }

    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void scaling(int x, int y);
    }
}
