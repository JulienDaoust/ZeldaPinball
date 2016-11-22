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
    /// Etat dans lequel on effectue les rotations
    /// </summary>
    class RotationState : AbstractState
    {
        /// <summary>
        /// On effectue la rotaion des objets selectionnes
        /// </summary>
        /// <param name="x">position en x de la souris</param>
        /// <param name="y">position en y de la souris</param>
        public override void Action(int x, int y)
        {
            if (lastPos_ != new Point())
            {
                double angle = (lastPos_.Y - y) / 400.0 * 360.0;
                FonctionsNatives.rotation(angle);
            }
            lastPos_ = new Point(x, y);

        }

        /// <summary>
        /// Dernier point de la souris(utile pour savoir si on monte ou descend)
        /// </summary>
        private Point lastPos_;
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rotation(double angle);
    }
}
