using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;
using WebDev.Models;

namespace WebDev.DAL
{
    public class WebDevInitializer : DropCreateDatabaseIfModelChanges<WebDevContext>
    {
        protected override void Seed(WebDevContext context)
        {
            var users = new List<User> {
                new User {
                    Username = "1110621",
                    PasswordHash = "B50D9DA273363ECCEF03008B2099D3EC"
                }
            };

            users.ForEach(u => context.Users.Add(u));
            context.SaveChanges();
        }
    }
}
