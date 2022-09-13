using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using Math; unneeded

namespace EDCHOST24
{
    public class Dot
    {
        public int x;
        public int y;


        public Dot(int _x = 0, int _y = 0)
        {
            x = _x;
            y = _y;
        }

        public static bool operator ==(Dot a, Dot b)
        {
            return (a.x == b.x) && (a.y == b.y);
        }

        public static bool operator !=(Dot a, Dot b)
        {
            return !(a == b);
        }

        public static int Distance(Dot A, Dot B)
        {
            return (int)Math.Sqrt((A.x - B.x) * (A.x - B.x)
                + (A.y - B.y) * (A.y - B.y));
            // return int
        }

        //由于每个package、station和wall都要进行legal检测，故而用静态在每个类里检测
        //最终函数汇总在Dot里，作为静态函数重用
        //现保证station和wall的illegal半径为10  8/9 ybj
        public static bool IsPosLegal(Dot adot)
        {
            return (!PackageList.IsPackageExisted(adot)) && (!Station.isCollided(adot, 10)) && (!Labyrinth.isCollided(adot, 10));
        }
    }
}
