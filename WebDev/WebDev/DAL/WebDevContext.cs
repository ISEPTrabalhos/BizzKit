using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Entity;
using WebDev.Models;

namespace WebDev.DAL
{
    public class WebDevContext : DbContext
    {
        public WebDevContext()
            : base("WebDevContext")
        {

        }

        public DbSet<User> Users { get; set; }
    }
}
