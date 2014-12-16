using WebDev.DAL;
using WebDev.Models;
using Microsoft.AspNet.Identity;
using System.Linq;
using WebDev.Controllers;
using Microsoft.AspNet.Identity.EntityFramework;

namespace WebDev.Services
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service" in code, svc and config file together.
    // NOTE: In order to launch WCF Test Client for testing this service, please select Service.svc or Service.svc.cs at the Solution Explorer and start debugging.
    public class Service : IService
    {
        private WebDevContext db = new WebDevContext();

        public int Login(string username, string password)
        {

            var passwordHash = AccountController.ConvertPasswordMd5(password);

            var user = from u in db.Users
                       where u.Username == username
                       && u.PasswordHash == passwordHash
                       select u;

            if (user.Count() == 1)
            {
                var context = new ApplicationDbContext();

                var appUser = from u in context.Users
                              where u.UserName == username
                              select u;

                if (appUser.Count() == 1)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        
        public int Score(string username, int score)
        {
            return 1;
        }
    }
}
