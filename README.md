# Minishell
Minishell est le second projet de la branche système du cursus de l'école 42.
Le but étant de coder en C un shell minimaliste. Voici les consignes à suivre:

    Vous devez programmer un mini interpréteur de commandes UNIX.
    • Cet interpréteur doit afficher un prompt (un simple "$> " par exemple)
    et attendre que vous tapiez une ligne de commande, validée par un retour à la ligne.
    • Le prompt n’est de nouveau affiché qu’après la fin de l’exécution de la commande.
    • Les lignes de commande sont simples, pas de pipes, pas de redirections ou
    autres fonctions avancées.
    • Les exécutables sont ceux que l’on peut trouver dans les chemins indiqués dans
    la variable PATH.
    • Dans le cas où l’exécutable ne peut être trouvé, il faut afficher un message
    d’erreur et réafficher le prompt.
    • Vous devez gérer les erreurs sans utiliser errno, en affichant un message adapté
    sur la sortie d’erreur.
    • Vous devez gérer correctement le PATH et l’environnement (copie du char **environ
    système).
    • Vous devez implémenter une série de builtins : echo, cd, setenv, unsetenv, env,
    exit.
    • Vous choisissez le shell de référence que vous souhaitez.
J'ai également ajouté la possibilité de modifier la ligne de commande en cours d'écriture ainsi qu'un historique
permettant de récupérer les lignes de commandes précédemment exécutées avec les flèches du clavier.
Mon minishell gère aussi les quotes simples et doubles ainsi que les échappements utilisant le caractère '\'.
# Compilation (gcc ou clang)
(Attention: ce projet à été réalisé pour Mac OS X Sierra, il pourrait y avoir des erreurs de compilation sur d'autres systèmes)
Pour compiler le projet lancez simplement la commande:

    make
à la racine du projet, l'exécutable 'minishell' sera créé dans ce même répertoire.
# Utilisation
Exécuter la commande:

    ./minishell
Le minishell est très simple mais parfaitement fonctionnel.
