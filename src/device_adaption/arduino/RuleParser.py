class RuleParser:
    def __init__(self, data):
        '''
        Construct RuleParser object.
        '''
        self._delim_initial = '++++'
        self._delim_final = '===='
        self._data = data + [self._delim_initial]
        self._labels = set()
        self._rules = list()
        self._build_ruleset()

    def __len__(self):
        return len(self._rules)

    def __iter__(self):
        '''
        Iterates over rules parsed by the object.
        '''
        return iter(self._rules)

    def __next__(self):
        '''
        Return next rule in iteration.
        '''
        for item in self._rules:
            yield item

    def _build_ruleset(self):
        if not self._data:
            raise Exception('Ruleset has not been imported.')
        rule_start_points = [
                    i 
                    for i, val in enumerate(self._data) 
                    if val == self._delim_initial
                ]
        for i in range(len(rule_start_points) - 1):
            # extract relevant lines
            rule = self._data[rule_start_points[i]+1:rule_start_points[i+1]]
            initial = rule[:rule.index(self._delim_final)]
            final = rule[rule.index(self._delim_final) + 1:]

            # set up local data
            # nodes are modeled as:
            # nodes = {
            #   id : { initial: X, final: Y }
            nodes = dict()
            # build node data
            for line in initial:
                if not line: continue
                node_data = line.split()[0]
                name, label = node_data.split(':')
                self._labels.add(label)
                nodes[name] = { 'initial': label }
            for line in final:
                if not line: continue
                node_data = line.split()[0]
                name, label = node_data.split(':')
                self._labels.add(label)
                nodes[name]['final'] = label

            # check that all involved nodes contain initial and final values
            for n in nodes:
                if 'initial' not in nodes[n] or 'final' not in nodes[n]:
                    raise KeyError('A parsed rule did not contain initial and final states. Rule was: ', n, ': ', nodes[n])

            # add new rule to ruleset
            parsed_rule = tuple([(nodes[n]['initial'], nodes[n]['final']) for n in nodes])
            self._rules.append(parsed_rule)

