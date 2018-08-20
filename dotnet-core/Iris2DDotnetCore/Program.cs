using System;
using System.Diagnostics;
using System.Net.Mime;
using System.Net.WebSockets;
using Iris2D.Core;
using Iris2DNativeBridge;

namespace Iris2D
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Begin...");

            ApplicationFactory.InitApiType(ApplicationFactory.GameApiType.OpenGL);

            //var result = Application.Instance.Initialize(1600, 1200, () =>
            //{
            //    while (!Application.Instance.IsQuited)
            //    {
            //        Graphics.Instance.Update();
            //    }
            //    return true;
            //}, "My Iris App");
            var result = Application.Instance.Initialize(new Application.AppStartupInfo()
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

            if (!result)
            {
                Application.Instance.Release();
            }
            else
            {
                Application.Instance.Run();
            }

        }
    }
}
