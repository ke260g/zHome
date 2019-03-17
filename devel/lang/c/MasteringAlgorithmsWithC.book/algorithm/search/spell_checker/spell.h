#ifndef SPELL_H
#define SPELL_H

/* define the maximum size for words in the dictionary */
#define SPELL_SIZE 31

/* public interface */
int spell(char (* dictionary)[SPELL_SIZE],
        int size,
        const char *word);

#endif
