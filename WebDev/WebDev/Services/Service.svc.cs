using WebDev.DAL;
using WebDev.Models;
using Microsoft.AspNet.Identity;
using System.Linq;
using WebDev.Controllers;
using Microsoft.AspNet.Identity.EntityFramework;
using System.Collections.Generic;

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

            var users = from u in db.Users
                        where u.username == username
                        && u.passwordHash == passwordHash
                        select u;

            if (users.Count() == 1)
            {
                var context = new ApplicationDbContext();

                var appUsers = from u in context.Users
                               where u.UserName == username
                               select u;

                if (appUsers.Count() == 1)
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
        
        public int Score(string username, string levelName, int score)
        {
            var users = from u in db.Users
                        where u.username == username
                        select u;

            if(users.Count() == 1)
            {
                var scores = from s in db.Scores
                             where s.username == username
                             && s.levelName == levelName
                             select s;

                if (scores.Count() == 0)
                {
                    Score s = new Score { username = username, levelName = levelName, score = score };
                    db.Scores.Add(s);
                }
                else
                {
                    scores.First().score = score;
                }

                db.SaveChanges();

                return 1;
            }
            else
            {
                return 0;
            }
        }

        public string[] ListLevels()
        {
            var levels = from l in db.Levels
                         select l;

            List<string> listLevels = new List<string>();

            foreach (var level in levels)
            {
                listLevels.Add(level.name);
            }

            return listLevels.ToArray();
        }
    }
}
