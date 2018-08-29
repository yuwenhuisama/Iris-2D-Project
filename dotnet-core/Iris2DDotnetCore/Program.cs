using System;
using Iris2D.Core;
using Iris2D.NativeBridge;

namespace Iris2D
{
    class Program
    {
        private static void Main(string[] args)
        {
            Console.WriteLine("Begin...");

            ApplicationFactory.InitApiType(ApplicationFactory.GameApiType.OpenGL);

            try
            {
                Application.Instance.Initialize(new Application.AppStartupInfo()
                {
                    GameFunc = () =>
                    {
                        while (!Application.Instance.IsQuited)
                        {
                            Graphics.Instance.Update();
                        }

                        return true;
                    },
                    Width = 1600,
                    Height = 1200,
                    X = 400,
                    Y = 400,
                    Title = "Iris 2D Application",
                });

                Application.Instance.Run();
            }
            catch(Iris2DNativeException e)
            {
                Console.WriteLine(e.Message);
            }
            finally
            {
                Application.Instance.Release();
            }

        }
    }
}
