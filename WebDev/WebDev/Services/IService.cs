using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace WebDev.Services
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService" in both code and config file together.
    [ServiceContract]
    public interface IService
    {
        [OperationContract]
        int Login(string username, string password);

        [OperationContract]
        void Score(string username, string levelName, int score);

        [OperationContract]
        string ListLevels();

        [OperationContract]
        string LoadLevel(string levelName);

        [OperationContract]
        string getTexturesList();
        
        [OperationContract]
        string downloadTexture(string textureName);

        [OperationContract]
        string getSoundsList();

        [OperationContract]
        string downloadSound(string soundName);

        [OperationContract]
        void uploadRoute(string username, string level, string route);
    }
}
