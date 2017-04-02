var trie_data="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";