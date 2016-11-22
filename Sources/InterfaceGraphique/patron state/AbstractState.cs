using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique.patron_state
{
    /// <summary>
    /// Classe abstraite des differents etats du mode editeur
    /// </summary>
    abstract class AbstractState
    {
        /// <summary>
        /// Fonction virtuelle des differents etats(rotation, translation, etc..)
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public abstract void Action(int x, int y);
    }
}
