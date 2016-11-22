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
    /// Etat de selection
    /// </summary>
    class ViewOrthoState : AbstractState
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public override void Action(int x, int y)
        {
            if (lastPos_ != new Point())
            {
                FonctionsNatives.translater(lastPos_.X - x,y-lastPos_.Y);
                lastPos_ = new Point(x, y);
            }
        }
        public void init(int x, int y)
        {
            lastPos_ = new Point(x, y);
        }
        private Point lastPos_;
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translater(double deplacementX, double deplacementY);
    }
}
