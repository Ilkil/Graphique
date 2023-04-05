/*void ViewerEtudiant::extrusion(Point Courbe[], Point Forme[], int taillecourbe){

    m_extrusion = Mesh(GL_TRIANGLE_STRIP);

    for(int i=0; i<taillecourbe; i++){ //Boucle sur la courbe
        for(int j=0; i<4; i++){ //Boucle sur la forme

            int m = (j + 1)% 4; //figure n'a que 4 points donc on fais % pou ne pas dépacer la capacité mais on a besoin de retourner sur le premier point pour fermer la figure
            int l = (i + 1) % taillecourbe;

            Vector a = normalize(Forme[j+1] - F[j]);
            Vector b = normalize(Vector(Courbe[i]));
            Vector normale = cross(a,b); //Produit vectoriel pour touver la normale a chaque face

            if(j == 3){ // refermer la dernière face
                m_extrusion.vertex(Forme[j]);
                m_extrusion.vertex(Forme[0]);
                m_extrusion.vertex(Forme[j] + Courbe[i]);
                m_extrusion.vertex(Forme[0] + Courbe[i]);

                //Apres avoir referemé la dernière face on déplace la forme d'un étage
                for(int k=0; k<4; k++){
                    Forme[k] = Forme[k] + Courbe[i];
                }
            }
            else{
                m_extrusion.vertex(Forme[j]);
                m_extrusion.vertex(Forme[j+1]);
                m_extrusion.vertex(Forme[j] + Courbe[i]);
                m_extrusion.vertex(Forme[j+1] + Courbe[i]);
            }
            m_extrusion.restart_strip();
        }
    }
}*/


void ViewerEtudiant::init_extrusion(Point Courbe[], Point Forme[], int taillecourbe){

    m_extrusion = Mesh(GL_TRIANGLE_STRIP);

    for(int i=0; i<taillecourbe; i++){ //Boucle sur la courbe
        for(int j=0; i<4; i++){ //Boucle sur la forme
            if(j != 3){ 
                m_extrusion.vertex(Forme[j]);
                m_extrusion.vertex(Forme[j+1]);
                m_extrusion.vertex(Forme[j] + Courbe[i]);
                m_extrusion.vertex(Forme[j+1] + Courbe[i]);


            }
            else{   
                m_extrusion.vertex(Forme[j]);
                m_extrusion.vertex(Forme[0]);
                m_extrusion.vertex(Forme[j] + Courbe[i]);
                m_extrusion.vertex(Forme[0] + Courbe[i]);
                
                for(int k=0; k<4; k++){
                    Forme[k] = Forme[k] + Courbe[i];
                }
            }
            m_extrusion.restart_strip();
        }
    }
}



/* Initialisation de l'objet auquel on fait une extrusion */
void ViewerEtudiant::init_extrusion(Point Figure[], Point Courbe[])
{
    m_extrusion = Mesh(GL_TRIANGLE_STRIP); // Choix primitive OpenGL.
    
    for(int i = 0 ; i < 2 ; i++) // Prend les points du tableau Courbe[].
    {
        for(int j = 0 ; j < 4 ; j++) // Prend les points du tableau Figure[].
        {
            Vector a, b, vec;
            Vector Normal[2][4];

            int k = (j + 1) % 4;
            int l = (i + 1) % 2;
            
            a = normalize(Figure[j] - Figure[k%4]);
            b = normalize(Figure[j] - (Figure[j] + Vector(Courbe[i])));

            vec = cross(a, b); // Produit Vectorial de a et b.
            
            if ( (k < 4) && (i < 2) )
            {
                // On crée les normales de l'extrusion.
                Normal[i][j] = vec + Vector(Figure[j]);
                Normal[l][j] = vec + Vector(Figure[j]) + Vector(Courbe[i]);
                Normal[l][k] = vec + Vector(Figure[k]) + Vector(Courbe[i]);
                Normal[i][k] = vec + Vector(Figure[k]);
            // Lorsque j est compris entre 0 et 2.
                if (j != 3)
                {
                    /* Dessine une face :
                     (Figure[j] + courbe[i])----------(Figure[j+1] + courbe[i])
                     |                                                        |
                     |                                                        |
                     Figure[j]--------------------------------------Figure[j+1]
                    */
                    m_extrusion.vertex(Figure[j].x + Courbe[i].x, Figure[j].y + Courbe[i].y, Figure[j].z + Courbe[i].z);
                    m_extrusion.vertex(Figure[j]);
                    m_extrusion.vertex(Figure[j+1].x + Courbe[i].x, Figure[j+1].y + Courbe[i].y, Figure[j+1].z + Courbe[i].z);
                    m_extrusion.vertex(Figure[j+1]);
                }
                // Pour relier le dernier point avec le premier.
                else
                {
                    m_extrusion.vertex(Figure[j].x + Courbe[i].x, Figure[j].y + Courbe[i].y, Figure[j].z + Courbe[i].z);
                    m_extrusion.vertex(Figure[j]);
                    m_extrusion.vertex(Figure[0].x + Courbe[i].x, Figure[0].y + Courbe[i].y, Figure[0].z + Courbe[i].z);
                    m_extrusion.vertex(Figure[0]);
                }
                
                m_extrusion.restart_strip(); // Démarre un nouveau strip.
                if(j != 0)
                {
                    // Pour éviter que lorsqu'on additionne notre point 0 à la première itération et qu'on en a besoin à la fin, qu'il est déjà été modifié.
                    Figure[j].x = Figure[j].x + Courbe[i].x;
                    Figure[j].y = Figure[j].y + Courbe[i].y;
                    Figure[j].z = Figure[j].z + Courbe[i].z;
                    // Evite les pics probables.
                    
                    // Normal de l'extrusion quand j != 0.
                    Normal[i][j] = Normal[i][j] / 4;
                }
            }
        }
        // Pour dessiner entre deux points.
        Figure[0].x = Figure[0].x + Courbe[i].x;
        Figure[0].y = Figure[0].y + Courbe[i].y;
        Figure[0].z = Figure[0].z + Courbe[i].z;
    }
}
