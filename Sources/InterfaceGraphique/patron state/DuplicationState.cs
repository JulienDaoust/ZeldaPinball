using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

namespace InterfaceGraphique.patron_state
{
    /// <summary>
    /// Etat de duplication
    /// </summary>
    class DuplicationState : AbstractState
    {
        /// <summary>
        /// On duplique les objets selectionnees
        /// </summary>
        /// <param name="x">Position en x du clique</param>
        /// <param name="y">Position en y du clique</param>
        public override void Action(int x, int y)
        {
            FonctionsNatives.duplication(x, y);
        }
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void duplication(int x, int y);
    }
}
