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
                    Username = "test",
                    PasswordHash = "098F6BCD4621D373CADE4E832627B4F6"
                }
            };

            users.ForEach(u => context.Users.Add(u));
            context.SaveChanges();
        }
    }
}
