using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace WebDev.Models
{
    public class User
    {
        [Key]
        public string Username { get; set; }

        [Required]
        public string PasswordHash { get; set; }
    }
}
