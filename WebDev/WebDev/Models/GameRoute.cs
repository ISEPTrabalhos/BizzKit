using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebDev.Models
{
    public class GameRoute
    {
        [Key]
        public int ID { get; set; }

        [Required]
        public string username { get; set; }

        [Required]
        public string level { get; set; }

        [Required]
        public string route { get; set; }
    }
}